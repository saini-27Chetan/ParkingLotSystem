#include<bits/stdc++.h>
#include"ParkingSpot.h"
using namespace std;


int main(){
    Vehicle vehicle("HR26AB1234","Car");
    ParkingSpot spot("A1","Car");

    cout<<"Spot ID: "<<spot.getSpotId()<<"\n";
    cout<<"Spot Type: "<<spot.getSpotType()<<"\n";
    cout<<"Occupied: "<<spot.isOccupied()<<"\n";

    bool parked=spot.parkVehicle(&vehicle);
    
    cout<<"Vehicle Parked: "<<parked<<"\n";
    cout<<"Occupied: "<<spot.isOccupied()<<"\n";

    if(spot.getVehicle()!=nullptr)
        cout<<"Vehicle: "<<spot.getVehicle()->getRegistrationNumber()<<"\n";

    spot.removeVehicle();
    cout<<"Occupied After Exit: "<<spot.isOccupied()<<"\n";

    return 0;
}