// Developed by Mohammad Mahdi Ramezanpour, Feb. 2020 (i@ramezanpour.net)

#include "Calculations.h"

Calculations::Calculations(int threshold) : m_threshold(threshold)
{
}

const std::vector<std::string> split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

void Calculations::ResetCalculationTime()
{
    m_nextCalculationTime = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now() + std::chrono::seconds(m_threshold));
}

void Calculations::FillBeacons(const std::vector<Beacon> &beacons)
{
    for (auto beacon : beacons)
    {
        m_beacons.push_back(beacon);
    }

    // TODO: After 2 seconds.
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if (now >= m_nextCalculationTime)
    {
        SelectBestBeaconsToProcess();
        RemoveWeakBeacons();
        m_callbackFunc(CalculateLocation());

        ResetCalculationTime();
        // Cleaning up beacon list for next calculation.
        m_beacons.clear();
    }
}

Beacon Calculations::ParseBeacon(const std::string &str)
{
    Beacon result;
    char *c_str = const_cast<char *>(str.c_str());
    char *splitted = strtok(c_str, "\t");
    int index = 0;
    while (splitted != NULL)
    {
        switch (index)
        {
        case 0:
            result.uniqueIdentifier = splitted;
            break;
        case 1:
            result.major = std::stoi(splitted);
            break;
        case 2:
            result.minor = std::stoi(splitted);
            break;
        case 3:
            result.distant = std::stod(splitted);
            break;
        case 4:
            result.transmissionPower = std::stoi(splitted);
            break;
        case 5:
            result.location.x = std::stod(splitted);
            break;
        case 6:
            result.location.y = std::stod(splitted);
            break;
        case 7:
            result.mRssi = std::stoi(splitted);
            break;
        case 8:
            result.rssi = std::stoi(splitted);
            break;
        }
        splitted = strtok(NULL, "\t");

        index++;
    }

    return result;
}

const Point Calculations::CalculateLocation()
{
    Point result;
    if (m_beaconsToProcess.size() < 3)
    {
        // Cannot determine location with less than 3 beacons.
        result.x = -1;
        result.y = -1;
        return result;
    }

    double normalizeCoefficient = 0.0;
    for (unsigned int i = 0; i < m_beaconsToProcess.size(); i++)
    {
        normalizeCoefficient += 1.0 / fabs(m_beaconsToProcess[i].distant);
    }

    std::vector<double> weight(m_beaconsToProcess.size(), 0.0);

    for (unsigned int i = 0; i < m_beaconsToProcess.size(); i++)
    {
        weight[i] += 1.0 / (fabs(m_beaconsToProcess[i].distant * normalizeCoefficient));
        result.x += weight[i] * m_beaconsToProcess[i].location.x;
        result.y += weight[i] * m_beaconsToProcess[i].location.y;
    }

    if (fabs(m_lastLocation.x - result.x) > 3)
    {
        result.x = m_lastLocation.x > result.x ? m_lastLocation.x - 1.0 : m_lastLocation.x + 1.0;
    }

    if (fabs(m_lastLocation.y - result.y) > 3)
    {
        result.y = m_lastLocation.y > result.y ? m_lastLocation.y - 1.0 : m_lastLocation.y + 1.0;
    }

    m_lastLocation = result;
    m_lastKnownLocations.push(m_lastLocation);
    if (m_lastKnownLocations.size() > 100)
    {
        m_lastKnownLocations.pop();
    }

    return result;
}

void Calculations::StartCalculations(const std::function<void(Point)> &callback)
{
    m_callbackFunc = callback;
    ResetCalculationTime();
}

void Calculations::SetRecognizedBeacons(const std::vector<Beacon> &recognizedBeacons)
{
    m_recognizedBeacons = recognizedBeacons;
}

const std::vector<Beacon> Calculations::ParseBeacons(const std::string &str)
{
    auto parsedBeacons = split(str, "\n");
    auto result = std::vector<Beacon>();
    for (auto item : parsedBeacons)
    {
        result.push_back(ParseBeacon(item));
    }

    return result;
}

void Calculations::SelectBestBeaconsToProcess()
{
    m_beaconsToProcess.clear();
    for (auto beacon : m_beacons)
    {
        Beacon correspondingBeacon;
        if (IsRecognized(beacon, correspondingBeacon) && !IsDuplicate(beacon))
        {
            double distance = CalculateAvgDistance(beacon);
            correspondingBeacon.distant = distance;
            correspondingBeacon.mRssi = beacon.mRssi;
            correspondingBeacon.transmissionPower = beacon.transmissionPower;
            m_beaconsToProcess.push_back(correspondingBeacon);
        }
    }
}

double Calculations::CalculateAvgDistance(Beacon &beacon)
{
    std::map<double, int> distances;
    for (auto b : m_beacons)
    {
        if (b == beacon)
        {
            auto item = distances.find(b.distant);
            distances[b.distant] = item != distances.end() ? item->second + 1 : 1;
        }
    }

    double selectedDistance = 0;
    int mostData = 0;

    for (auto item : distances)
    {
        if (item.second >= mostData)
        {
            selectedDistance = item.first;
            mostData = item.second;
        }
    }

    return selectedDistance;
}

bool Calculations::IsDuplicate(const Beacon &b)
{
    for (auto beacon : m_beaconsToProcess)
    {
        if (beacon == b)
            return true;
    }

    return false;
}

bool Calculations::IsRecognized(const Beacon &b, Beacon &correspondingBeacon)
{
    for (auto beacon : m_recognizedBeacons)
    {
        if (beacon == b)
        {
            correspondingBeacon = beacon;
            return true;
        }
    }

    return false;
}

void Calculations::RemoveWeakBeacons()
{
    if (m_beaconsToProcess.size() <= 3)
    {
        return;
    }
    else
    {
        std::sort(m_beaconsToProcess.begin(), m_beaconsToProcess.end(),
                  [](Beacon b1, Beacon b2) {
                      return b1.distant > b2.distant;
                  });

        m_beaconsToProcess.erase(m_beaconsToProcess.begin() + 2,
                                 m_beaconsToProcess.end());
    }
}
