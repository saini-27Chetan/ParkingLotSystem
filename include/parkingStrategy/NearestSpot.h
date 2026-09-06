#ifndef NEARESTSPOT_H
#define NEARESTSPOT_H

#include<bits/stdc++.h>
#include"ParkingSpotStrategy.h"
using namespace std;

class NearestSpot:public ParkingSpotStrategy{
public:
    ParkingSpot* findSpot(vector<ParkingSpot*>& spots, string vehicleType) override;
};

#endif