#include<bits/stdc++.h>
#include"ParkingSpot.h"
using namespace std;

ParkingSpot::ParkingSpot(string spotId, string spotType, Position position){
    this->spotId=spotId;
    this->spotType=spotType;
    occupied=false;
    vehicle=nullptr;
    this->position=position;
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
    notifyObservers();

    return true;
}

void ParkingSpot::removeVehicle(){
    vehicle=nullptr;
    occupied=false;
    notifyObservers();
}

Vehicle* ParkingSpot::getVehicle(){
    return vehicle;
}

void ParkingSpot::addObserver(ParkingObserver* observer){
    observers.push_back(observer);
}

void ParkingSpot::notifyObservers(){
    for(ParkingObserver* observer : observers)
        observer->update(spotId, occupied);
}

Position ParkingSpot::getPosition(){
    return position;
}