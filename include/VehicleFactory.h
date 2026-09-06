#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H

#include<bits/stdc++.h>
#include"Vehicle.h"
using namespace std;

class VehicleFactory{
public:
    static Vehicle* createVehicle(string registrationNumber, string vehicleType);
};

#endif