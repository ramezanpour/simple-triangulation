#include <iostream>
#include "Calculations.h"
#include <vector>

void printVector(std::vector<Beacon> &beacons)
{
    for (auto beacon : beacons)
    {
        printf("Major: %d, Minor: %d, Distance: %f, LocationX: %f, LocationY: %f, TX power: %d, mRSSI: %d, RSSI: %d\n",
               beacon.major,
               beacon.minor,
               beacon.distant,
               beacon.location.x,
               beacon.location.y,
               beacon.transmissionPower,
               beacon.mRssi,
               beacon.rssi);
    }
}

void callback(Point p)
{
    printf("Point: %f, %f\n", p.x, p.y);
}

int main()
{

    Calculations calc(3);
    //const std::string str = "23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t207\t1.9\t-16\t58.58812\t59.461716\t-83\t-89\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t200\t1.25\t-16\t55.426596\t25.951728\t-83\t-89\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t213\t2.2\t-16\t58.747376\t47.79768\t-83\t-90\n";
    //const std::string str = "23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t207\t4.47\t-16\t54.69\t29.51\t-83\t-89\n"
    //"23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t200\t14.13\t-16\t54.68\t29.51\t-83\t-89\n"
    //"23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t213\t15.85\t-16\t49.05\t32.16\t-83\t-90\n";
    const std::string recognizeBeaconsStr = "23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t207\t0.0\t-20\t58.65\t59.46\t-87\t0\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t208\t0.0\t-20\t20.0\t20.0\t-87\t0\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t217\t0.0\t-20\t10.0\t8.0\t-87\t0\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t219\t0.0\t-20\t7.0\t55.0\t-87\t0\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t224\t0.0\t-20\t60.0\t30.0\t-87\t0\n";
    auto recognizedBeacons = calc.ParseBeacons(recognizeBeaconsStr);
    //printVector(recognizedBeacons);
    calc.SetRecognizedBeacons(recognizedBeacons);
    const std::string beaconsStr = "23A01AF0-232A-4518-9C0E-323FB773F5EF\t00001\t00219\t0.15848932\t-87\t0.0\t0.0\t0.0\t-71\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t00001\t00207\t0.1\t-87\t0.0\t0.0\t0.0\t-67\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t00001\t00224\t0.07943282\t-83\t0.0\t0.0\t0.0\t-61\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t00001\t00211\t1.2589254\t-83\t0.0\t0.0\t0.0\t-85\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t00001\t00208\t0.070794575\t-87\t0.0\t0.0\t0.0\t-64\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t00001\t00217\t0.22387211\t-87\t0.0\t0.0\t0.0\t-74\n";
    auto beacons = calc.ParseBeacons(beaconsStr);
    //printVector(recognizedBeacons);
    calc.FillBeacons(beacons);
    calc.StartCalculations(callback);

    //printf("X: %lf, Y: %lf\n", point.x, point.y);
    return 0;
}
