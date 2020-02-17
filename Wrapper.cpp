#include "Calculations.h"
#include <string>
#include "Point.h"
#include <cstdio>

Calculations c;

void SetRecognizedBeacons(std::string &beacons_str)
{
    auto beacons = c.ParseBeacons(beacons_str);
    c.SetRecognizedBeacons(beacons);
}

char *CalculateLocation(std::string &beacons_str)
{
    auto beacons = c.ParseBeacons(beacons_str);
    c.FillBeacons(beacons);

    auto point = c.CalculateLocation();
    char result[50];
    sprintf(result, "%lf,%lf", point.x, point.y);

    return result;
}
