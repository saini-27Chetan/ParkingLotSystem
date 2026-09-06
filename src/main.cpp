#include<bits/stdc++.h>
#include"VehicleFactory.h"
#include"ParkingSpotFactory.h"
#include"parkingStrategy/FirstAvailableSpot.h"
#include"parkingStrategy/NearestSpot.h"
using namespace std;

int main(){
    Vehicle* car=VehicleFactory::createVehicle("HR26AB1234","Car");
    Vehicle* bike=VehicleFactory::createVehicle("HR26CD5678","Bike");
    Vehicle* electric=VehicleFactory::createVehicle("HR26EF9012","Electric");

    ParkingSpot* spot1=ParkingSpotFactory::createParkingSpot("A1","Bike");
    ParkingSpot* spot2=ParkingSpotFactory::createParkingSpot("A2","Compact");
    ParkingSpot* spot3=ParkingSpotFactory::createParkingSpot("A3","Large");
    ParkingSpot* spot4=ParkingSpotFactory::createParkingSpot("A4","Electric");

    vector<ParkingSpot*> spots;

    spots.push_back(spot1);
    spots.push_back(spot2);
    spots.push_back(spot3);
    spots.push_back(spot4);

    FirstAvailableSpot firstAvailableSpot;

    ParkingSpot* carSpot=firstAvailableSpot.findSpot(spots,car->getVehicleType());
    if(carSpot!=nullptr){
        carSpot->parkVehicle(car);
        cout<<"Car parked at: "<<carSpot->getSpotId()<<"\n";
    }
    else
        cout<<"No suitable spot available for Car\n";

    ParkingSpot* bikeSpot=firstAvailableSpot.findSpot(spots,bike->getVehicleType());
    if(bikeSpot!=nullptr){
        bikeSpot->parkVehicle(bike);
        cout<<"Bike parked at: "<<bikeSpot->getSpotId()<<"\n";
    }
    else
        cout<<"No suitable spot available for Bike\n";


    NearestSpot nearestSpot;

    ParkingSpot* electricSpot=nearestSpot.findSpot(spots,electric->getVehicleType());
    if(electricSpot!=nullptr){
        electricSpot->parkVehicle(electric);
        cout<<"Electric vehicle parked at: "<<electricSpot->getSpotId()<<"\n";
    }
    else
        cout<<"No suitable spot available for Electric vehicle\n";

    cout<<"\nParking Availability:\n";

    for(ParkingSpot* spot:spots){
        cout<<spot->getSpotId()<<" - "<<spot->getSpotType()<<" - ";
        spot->isOccupied() ? cout<<"Occupied\n" : cout<<"Available\n";
    }

    for(ParkingSpot* spot:spots)
        delete spot;

    delete car;
    delete bike;
    delete electric;

    return 0;
}