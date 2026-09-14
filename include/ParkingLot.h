#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include<bits/stdc++.h>
#include"ParkingSpotFactory.h"
using namespace std;

class ParkingLot{
public:
    vector<ParkingSpot*> createParkingSpots(
        int bikeCount,
        int compactCount,
        int largeCount,
        int electricCount
    );
};

#endif