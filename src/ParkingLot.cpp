#include<bits/stdc++.h>
#include"ParkingLot.h"
using namespace std;

vector<ParkingSpot*> ParkingLot::createParkingSpots(int bikeCount, int compactCount, int largeCount, int electricCount){
    vector<ParkingSpot*> spots;
    for(int i=1;i<=bikeCount;i++){
        string spotId="B"+to_string(i);
        spots.push_back(ParkingSpotFactory::createParkingSpot(spotId, "Bike"));
    }

    for(int i=1;i<=compactCount;i++){
        string spotId="C"+to_string(i);
        spots.push_back(ParkingSpotFactory::createParkingSpot(spotId, "Compact"));
    }

    for(int i=1;i<=largeCount;i++){
        string spotId="L"+to_string(i);
        spots.push_back(ParkingSpotFactory::createParkingSpot(spotId, "Large"));
    }

    for(int i=1;i<=electricCount;i++){
        string spotId="E"+to_string(i);
        spots.push_back(ParkingSpotFactory::createParkingSpot(spotId, "Electric"));
    }

    return spots;
}