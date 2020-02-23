#if !defined(CALCULATIONS_H)
#define CALCULATIONS_H

#include "Beacon.h"
#include "Point.h"
#include <vector>

class Calculations
{
public:
    const Point CalculateLocation();
    void FillBeacons(const std::vector<Beacon> &beacons);
    void SetRecognizedBeacons(const std::vector<Beacon> &recognizedBeacons);
    const std::vector<Beacon> ParseBeacons(const std::string &str);

private:
    std::vector<Beacon> m_recognizedBeacons;
    std::vector<Beacon> m_beacons;
    std::vector<Beacon> m_beaconsToProcess;

    void RemoveUnrecognizedBeacons();
    void RemoveWeakBeacons();
    bool IsInRecognizedBeacons(Beacon b, Beacon &correspondingBeacon);
    bool IsDuplicateBeacons(Beacon beacon);
    Beacon ParseBeacon(const std::string &str);
};

#endif // CALCULATIONS_H
