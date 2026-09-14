#include<bits/stdc++.h>
#include"ParkingLot.h"
using namespace std;

vector<ParkingSpot*> ParkingLot::createParkingSpots(int bikeCount, int compactCount, int largeCount, int electricCount){
    vector<ParkingSpot*> spots;
    const double SPOT_DISTANCE = 5.0, ROW_DISTANCE = 5.0;
    const int SPOTS_PER_ROW = 4;

    int currentIndex = 0;
    auto createSpots = [&](int count, string prefix, string spotType){
        for(int i = 1; i <= count; i++){
            string spotId = prefix + to_string(i);

            int row = currentIndex / SPOTS_PER_ROW;
            int column = currentIndex % SPOTS_PER_ROW;
            double x = column * SPOT_DISTANCE;
            double y = row * ROW_DISTANCE;
            Position position(x, y);

            spots.push_back(ParkingSpotFactory::createParkingSpot(spotId, spotType, position));
            currentIndex++;
        }
    };

    createSpots(bikeCount, "B", "Bike");
    createSpots(compactCount, "C", "Compact");
    createSpots(largeCount, "L", "Large");
    createSpots(electricCount, "E", "Electric");

    return spots;
}