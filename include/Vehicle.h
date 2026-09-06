#ifndef VEHICLE_H
#define VEHICLE_H

#include<bits/stdc++.h>
using namespace std;

class Vehicle{
    string registrationNumber;
    string vehicleType;
    
public:
    Vehicle(string registrationNumber, string vehicleType);

    string getRegistrationNumber();
    string getVehicleType();
};

#endif