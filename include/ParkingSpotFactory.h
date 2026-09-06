#ifndef PARKINGSPOTFACTORY_H
#define PARKINGSPOTFACTORY_H

#include<bits/stdc++.h>
#include"ParkingSpot.h"
using namespace std;

class ParkingSpotFactory{
public:
    static ParkingSpot* createParkingSpot(string spotId,string spotType);
};

#endif