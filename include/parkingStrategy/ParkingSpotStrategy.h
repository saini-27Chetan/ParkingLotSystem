#ifndef PARKINGSPOTSTRATEGY_H
#define PARKINGSPOTSTRATEGY_H

#include<bits/stdc++.h>
#include"ParkingSpot.h"
using namespace std;

class ParkingSpotStrategy{
public:
    virtual ParkingSpot* findSpot(vector<ParkingSpot*>& spots, string vehicleType)=0;
    virtual ~ParkingSpotStrategy(){}
};

#endif