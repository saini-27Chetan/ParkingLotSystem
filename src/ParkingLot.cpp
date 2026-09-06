#include<bits/stdc++.h>
#include"ParkingLot.h"
using namespace std;

vector<ParkingSpot*> ParkingLot::createParkingSpots(){
    int bikeCount;
    int compactCount;
    int largeCount;
    int electricCount;

    cout<<"Enter number of Bike spots: ";
    cin>>bikeCount;
    cout<<"Enter number of Compact spots: ";
    cin>>compactCount;
    cout<<"Enter number of Large spots: ";
    cin>>largeCount;
    cout<<"Enter number of Electric spots: ";
    cin>>electricCount;
    cout<<"\n";

    vector<ParkingSpot*> spots;
    for(int i=1;i<=bikeCount;i++){
        string spotId="B"+to_string(i);
        spots.push_back(ParkingSpotFactory::createParkingSpot(spotId,"Bike"));
    }

    for(int i=1;i<=compactCount;i++){
        string spotId="C"+to_string(i);
        spots.push_back(ParkingSpotFactory::createParkingSpot(spotId,"Compact"));
    }

    for(int i=1;i<=largeCount;i++){
        string spotId="L"+to_string(i);
        spots.push_back(ParkingSpotFactory::createParkingSpot(spotId,"Large"));
    }

    for(int i=1;i<=electricCount;i++){
        string spotId="E"+to_string(i);
        spots.push_back(ParkingSpotFactory::createParkingSpot(spotId,"Electric"));
    }

    return spots;
}