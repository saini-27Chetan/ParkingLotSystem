#include<bits/stdc++.h>
#include"VehicleFactory.h"
#include"ParkingSpotFactory.h"
#include"ParkingManager.h"
#include"parkingStrategy/FirstAvailableSpot.h"
#include"pricingStrategy/HourlyPrice.h"
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

    FirstAvailableSpot parkingStrategy;
    HourlyPrice pricingStrategy;

    ParkingManager parkingManager(spots, &parkingStrategy, &pricingStrategy);

    cout<<"Available spots before parking: ";
    cout<<parkingManager.getAvailableSpotCount()<<"\n";

    Ticket* carTicket=parkingManager.parkVehicle(car);
    if(carTicket!=nullptr){
        cout<<"Car parked successfully\n";
        cout<<"Ticket ID: "<<carTicket->getTicketId()<<"\n";
        cout<<"Spot: "<<carTicket->getParkingSpot()->getSpotId()<<"\n";
    }
    else
        cout<<"Car parking failed\n";

    Ticket* bikeTicket=parkingManager.parkVehicle(bike);
    if(bikeTicket!=nullptr){
        cout<<"\nBike parked successfully\n";
        cout<<"Ticket ID: "<<bikeTicket->getTicketId()<<"\n";
        cout<<"Spot: "<<bikeTicket->getParkingSpot()->getSpotId()<<"\n";
    }
    else
        cout<<"\nBike parking failed\n";

    Ticket* electricTicket=parkingManager.parkVehicle(electric);

    if(electricTicket!=nullptr){
        cout<<"\nElectric vehicle parked successfully\n";
        cout<<"Ticket ID: "<<electricTicket->getTicketId()<<"\n";
        cout<<"Spot: "<<electricTicket->getParkingSpot()->getSpotId()<<"\n";
    }
    else
        cout<<"\nElectric vehicle parking failed\n";

    cout<<"\nAvailable spots after parking: ";
    cout<<parkingManager.getAvailableSpotCount()<<"\n";

    Ticket* searchTicket=parkingManager.findTicket("T1");
    if(searchTicket!=nullptr){
        cout<<"\nTicket T1 found\n";
        cout<<"Vehicle: "<<searchTicket->getVehicle()->getRegistrationNumber()<<"\n";
        cout<<"Spot: "<<searchTicket->getParkingSpot()->getSpotId()<<"\n";
    }
    else
        cout<<"\nTicket T1 not found\n";

    double fee=parkingManager.exitVehicle("T1");

    if(fee>=0){
        cout<<"\nVehicle exited successfully\n";
        cout<<"Parking Fee: Rs. "<<fee<<"\n";
    }
    else
        cout<<"\nVehicle exit failed\n";

    cout<<"Available spots after exit: ";
    cout<<parkingManager.getAvailableSpotCount()<<"\n";

    for(ParkingSpot* spot:spots)
        delete spot;

    delete car;
    delete bike;
    delete electric;

    return 0;
}