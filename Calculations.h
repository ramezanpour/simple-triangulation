// Developed by Mohammad Mahdi Ramezanpour, Feb. 2020 (i@ramezanpour.net)

#if !defined(CALCULATIONS_H)
#define CALCULATIONS_H

#include "Beacon.h"
#include "Point.h"
#include <vector>
#include <ctime>
#include <chrono>
#include <math.h>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>
#include <stack>

class Calculations
{
public:
    Calculations(int thershold = 2);
    void StartCalculations(const std::function<void(Point)> &callback);
    void FillBeacons(const std::vector<Beacon> &beacons);
    void SetRecognizedBeacons(const std::vector<Beacon> &recognizedBeacons);
    const std::vector<Beacon> ParseBeacons(const std::string &str);

private:
    std::vector<Beacon> m_recognizedBeacons;
    std::vector<Beacon> m_beacons;
    std::vector<Beacon> m_beaconsToProcess;
    int m_threshold;
    time_t m_nextCalculationTime;
    std::function<void(Point)> m_callbackFunc;
    Point m_lastLocation;
    std::stack<Point> m_lastKnownLocations;

    void SelectBestBeaconsToProcess();
    void RemoveWeakBeacons();
    bool IsRecognized(const Beacon &b, Beacon &correspondingBeacon);
    bool IsDuplicate(const Beacon &beacon);
    const Point CalculateLocation();
    Beacon ParseBeacon(const std::string &str);
    void ResetCalculationTime();
    double CalculateAvgDistance(Beacon &beacon);
};

#endif // CALCULATIONS_H
