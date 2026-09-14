#include<bits/stdc++.h>
#include"parkingStrategy/NearestSpot.h"
using namespace std;

ParkingSpot* NearestSpot::findSpot(vector<ParkingSpot*>& spots, string vehicleType){
    const double entranceX = 0.0, entranceY = -8.0;
    ParkingSpot* nearestSpot = nullptr;
    double minimumDistance = numeric_limits<double>::max();
    
    for(ParkingSpot* spot : spots){
        if(spot->isOccupied())
            continue;

        string spotType = spot->getSpotType();
        bool compatible = false;

        if(vehicleType == "BIKE" && spotType == "Bike")
            compatible = true;
        else if(vehicleType == "CAR" && (spotType == "Compact" || spotType == "Large"))
            compatible = true;
        else if(vehicleType == "ELECTRIC" && spotType == "Electric")
            compatible = true;

        if(!compatible)
            continue;

        Position position = spot->getPosition();
        double dx = position.x - entranceX;
        double dy = position.y - entranceY;
        double distance = sqrt(dx * dx + dy * dy);

        if(distance < minimumDistance){
            minimumDistance = distance;
            nearestSpot = spot;
        }
    }

    return nearestSpot;
};