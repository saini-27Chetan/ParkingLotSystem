#include<bits/stdc++.h>
#include"parkingStrategy/FirstAvailableSpot.h"
using namespace std;

ParkingSpot* FirstAvailableSpot::findSpot(vector<ParkingSpot*>& spots, string vehicleType){
    for(ParkingSpot* spot:spots){
        if(!spot->isOccupied()){
            string spotType=spot->getSpotType();

            if(vehicleType=="BIKE" && spotType=="Bike")
                return spot;
            if(vehicleType=="CAR" && (spotType=="Compact" || spotType=="Large"))
                return spot;
            if(vehicleType=="ELECTRIC" && spotType=="Electric")
                return spot;
        }
    }

    return nullptr;
};