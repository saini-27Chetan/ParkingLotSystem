#include<bits/stdc++.h>
#include"ParkingSpotFactory.h"
using namespace std;

ParkingSpot * ParkingSpotFactory::createParkingSpot(string spotId, string spotType){
    return new ParkingSpot(spotId, spotType);
}