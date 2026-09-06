#ifndef PARKINGSPOT_H
#define PARKINGSPOT_H

#include<bits/stdc++.h>
#include"Vehicle.h"
#include"observer/ParkingObserver.h"
using namespace std;

class ParkingSpot{
    string spotId;
    string spotType;
    bool occupied;
    Vehicle* vehicle;
    vector<ParkingObserver*> observers;

public:
    ParkingSpot(string spotId, string spotType);

    string getSpotId();
    string getSpotType();
    bool isOccupied();

    bool parkVehicle(Vehicle* vehicle);
    void removeVehicle();
    Vehicle* getVehicle();
    void addObserver(ParkingObserver* observer);
};

#endif