#include <iostream>
#include "Calculations.h"
#include <vector>

int main()
{

    Calculations calc;
    const std::string str = "23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t207\t1.9\t-16\t58.58812\t59.461716\t-83\t-89\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t200\t1.25\t-16\t55.426596\t25.951728\t-83\t-89\n23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t213\t2.2\t-16\t58.747376\t47.79768\t-83\t-90\n";
    //const std::string str = "23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t207\t4.47\t-16\t54.69\t29.51\t-83\t-89\n"
    //"23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t200\t14.13\t-16\t54.68\t29.51\t-83\t-89\n"
    //"23A01AF0-232A-4518-9C0E-323FB773F5EF\t1\t213\t15.85\t-16\t49.05\t32.16\t-83\t-90\n";
    auto beacons = calc.ParseBeacons(str);
    calc.SetRecognizedBeacons(beacons);

    calc.FillBeacons(beacons);
    auto point = calc.CalculateLocation();

    printf("X: %lf, Y: %lf\n", point.x, point.y);
    return 0;
}
