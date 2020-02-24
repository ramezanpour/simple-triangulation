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

class Calculations
{
public:
    Calculations(int thershold = 2);
    const Point CalculateLocation();
    void FillBeacons(const std::vector<Beacon> &beacons);
    void SetRecognizedBeacons(const std::vector<Beacon> &recognizedBeacons);
    const std::vector<Beacon> ParseBeacons(const std::string &str);

private:
    std::vector<Beacon> m_recognizedBeacons;
    std::vector<Beacon> m_beacons;
    std::vector<Beacon> m_beaconsToProcess;
    int m_threshold;
    time_t m_lastBeaconClearanceTime;

    void RemoveUnrecognizedBeacons();
    void RemoveWeakBeacons();
    bool IsInRecognizedBeacons(const Beacon &b, Beacon &correspondingBeacon);
    bool IsDuplicateBeacons(const Beacon &beacon);
    Beacon ParseBeacon(const std::string &str);
};

#endif // CALCULATIONS_H
