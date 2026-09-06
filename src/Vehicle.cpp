#include<bits/stdc++.h>
using namespace std;

#include"Vehicle.h"

Vehicle::Vehicle(string registrationNumber,string vehicleType){
    this->registrationNumber=registrationNumber;
    this->vehicleType=vehicleType;
}

string Vehicle::getRegistrationNumber(){
    return registrationNumber;
}

string Vehicle::getVehicleType(){
    return vehicleType;
}