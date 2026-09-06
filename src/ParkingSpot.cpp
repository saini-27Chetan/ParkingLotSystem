#include<bits/stdc++.h>
#include"ParkingSpot.h"
using namespace std;

ParkingSpot::ParkingSpot(string spotId, string spotType){
    this->spotId=spotId;
    this->spotType=spotType;
    occupied=false;
    vehicle=nullptr;
}

string ParkingSpot::getSpotId(){
    return spotId;
}

string ParkingSpot::getSpotType(){
    return spotType;
}

bool ParkingSpot::isOccupied(){
    return occupied;
}

bool ParkingSpot::parkVehicle(Vehicle* vehicle){
    if(occupied)
        return false;

    this->vehicle=vehicle;
    occupied=true;

    return true;
}

void ParkingSpot::removeVehicle(){
    vehicle=nullptr;
    occupied=false;
}

Vehicle* ParkingSpot::getVehicle(){
    return vehicle;
}