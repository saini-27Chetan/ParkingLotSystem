#include<bits/stdc++.h>
#include"VehicleFactory.h"
#include"ParkingSpotFactory.h"
using namespace std;

int main(){
    Vehicle* vehicle=VehicleFactory::createVehicle("HR26AB1234","Car");

    ParkingSpot* spot=ParkingSpotFactory::createParkingSpot("A1","Compact");

    cout<<"Vehicle Registration Number: "<<vehicle->getRegistrationNumber()<<"\n";
    cout<<"Vehicle Type: "<<vehicle->getVehicleType()<<"\n";

    cout<<"Spot ID: "<<spot->getSpotId()<<"\n";
    cout<<"Spot Type: "<<spot->getSpotType()<<"\n";

    bool parked=spot->parkVehicle(vehicle);

    cout<<"Vehicle Parked: "<<parked<<"\n";
    cout<<"Spot Occupied: "<<spot->isOccupied()<<"\n";

    if(spot->getVehicle()!=nullptr){
        cout<<"Parked Vehicle: "<<spot->getVehicle()->getRegistrationNumber()<<"\n";
    }

    spot->removeVehicle();

    cout<<"Spot Occupied After Exit: "<<spot->isOccupied()<<"\n";

    delete spot;
    delete vehicle;

    return 0;
}