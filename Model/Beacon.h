// Developed by Mohammad Mahdi Ramezanpour, Feb. 2020 (i@ramezanpour.net)

#if !defined(BEACON_H)
#define BEACON_H

#include <string>
#include <stdint.h>
#include "Point.h"

struct Beacon
{
    int16_t rssi, transmissionPower;
    uint16_t major, minor;
    std::string uniqueIdentifier;
    double distant;

    Point location;
    uint16_t mRssi, advertisingInterval;

    bool operator==(const Beacon beacon)
    {
        if (beacon.major == major &&
            beacon.minor == minor &&
            beacon.uniqueIdentifier == uniqueIdentifier)
        {
            return true;
        }
        return false;
    }
};
#endif // BEACON_H
