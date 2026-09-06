#include<bits/stdc++.h>
#include"parkingStrategy/FirstAvailableSpot.h"
using namespace std;

ParkingSpot* FirstAvailableSpot::findSpot(vector<ParkingSpot*>& spots, string vehicleType){
    for(ParkingSpot* spot:spots){
        if(!spot->isOccupied()){
            string spotType=spot->getSpotType();

            if(vehicleType=="Bike" && spotType=="Bike")
                return spot;
            if(vehicleType=="Car" && (spotType=="Compact" || spotType=="Large"))
                return spot;
            if(vehicleType=="Electric" && spotType=="Electric")
                return spot;
        }
    }

    return nullptr;
};