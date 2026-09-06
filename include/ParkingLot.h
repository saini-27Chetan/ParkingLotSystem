#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include<bits/stdc++.h>
#include"ParkingSpotFactory.h"
using namespace std;

class ParkingLot{
public:
    vector<ParkingSpot*> createParkingSpots();
};

#endif