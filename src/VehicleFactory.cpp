#include<bits/stdc++.h>
#include"VehicleFactory.h"
using namespace std;

Vehicle* VehicleFactory::createVehicle(string registrationNumber, string vehicleType){
    return new Vehicle(registrationNumber, vehicleType);
}