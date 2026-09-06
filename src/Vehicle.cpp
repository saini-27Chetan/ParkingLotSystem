#include<bits/stdc++.h>
#include"Vehicle.h"
using namespace std;


Vehicle::Vehicle(string registrationNumber, string vehicleType){
    this->registrationNumber=registrationNumber;
    this->vehicleType=vehicleType;
}

string Vehicle::getRegistrationNumber(){
    return registrationNumber;
}

string Vehicle::getVehicleType(){
    return vehicleType;
}