#ifndef PARKINGSPOT_H
#define PARKINGSPOT_H

#include<bits/stdc++.h>
#include"Vehicle.h"
#include"observer/ParkingObserver.h"
using namespace std;

struct Position {
    double x;
    double y;

    Position(double x = 0, double y = 0) : x(x), y(y) {}
};

class ParkingSpot{
    string spotId;
    string spotType;
    bool occupied;

    Vehicle* vehicle;
    vector<ParkingObserver*> observers;
    Position position;

public:
    ParkingSpot(string spotId, string spotType, Position position);

    string getSpotId();
    string getSpotType();
    bool isOccupied();

    bool parkVehicle(Vehicle* vehicle);
    void removeVehicle();
    Vehicle* getVehicle();
    void addObserver(ParkingObserver* observer);
    void notifyObservers();
    Position getPosition();
};

#endif