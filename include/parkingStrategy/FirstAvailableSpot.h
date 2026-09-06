#ifndef FIRSTAVAILABLESPOT_H
#define FIRSTAVAILABLESPOT_H

#include<bits/stdc++.h>
#include"ParkingSpotStrategy.h"
using namespace std;

class FirstAvailableSpot:public ParkingSpotStrategy{
public:
    ParkingSpot* findSpot(vector<ParkingSpot*>& spots, string vehicleType) override;
};

#endif