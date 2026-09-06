#include<bits/stdc++.h>
#include"VehicleFactory.h"
#include"ParkingSpotFactory.h"
#include"ParkingManager.h"
#include"parkingStrategy/FirstAvailableSpot.h"
#include"parkingStrategy/NearestSpot.h"
#include"pricingStrategy/HourlyPrice.h"
#include"pricingStrategy/FlatRatePrice.h"
#include"observer/DisplayBoard.h"
#include"Logger.h"
using namespace std;

string toUpper(string value){
    for(auto& x:value)
        x=toupper(x);

    return value;
}

void parkVehicle(ParkingManager& parkingManager, vector<Vehicle*>& vehicles){
    string registrationNumber;
    string vehicleType;

    cout<<"Enter registration number: ";
    cin>>registrationNumber;
    cout<<"Enter vehicle type: ";
    cin>>vehicleType;

    registrationNumber=toUpper(registrationNumber);
    vehicleType=toUpper(vehicleType);

    if(vehicleType!="CAR" && vehicleType!="BIKE" && vehicleType!="ELECTRIC"){
        cout<<"Invalid vehicle type\n";
        return;
    }
    cout<<"\n";
    
    Vehicle* vehicle=VehicleFactory::createVehicle(registrationNumber,vehicleType);
    Ticket* ticket=parkingManager.parkVehicle(vehicle);

    if(ticket!=nullptr){
        vehicles.push_back(vehicle);
        cout<<"Vehicle parked successfully\n";
        cout<<"Ticket ID: "<<ticket->getTicketId()<<"\n";
        cout<<"Spot: "<<ticket->getParkingSpot()->getSpotId()<<"\n";
    }
    else{
        cout<<"Vehicle parking failed\n";
        delete vehicle;
    }
}

void exitVehicle(ParkingManager& parkingManager, vector<Vehicle*>& vehicles){
    string ticketId;

    cout<<"Enter ticket ID: ";
    cin>>ticketId;
    ticketId=toUpper(ticketId);
    cout<<"\n";

    Ticket* ticket=parkingManager.findTicket(ticketId);

    if(ticket==nullptr){
        cout<<"Invalid ticket ID\n";
        return;
    }

    Vehicle* vehicle=ticket->getVehicle();

    double fee=parkingManager.exitVehicle(ticketId);
    if(fee==-1){
        cout<<"Invalid ticket ID\n";
        return;
    }
    for(int i=0; i<vehicles.size(); i++){
        if(vehicles[i]==vehicle){
            delete vehicles[i];
            vehicles.erase(vehicles.begin()+i);
            break;
        }
    }
    cout<<"Vehicle exited successfully\n";
    cout<<"Parking Fee: Rs. "<<fee<<"\n";
}

void viewParkingAvailability(ParkingManager& parkingManager){
    int availableSpots=parkingManager.getAvailableSpotCount();
    cout<<"Available parking spots: "<<availableSpots<<"\n";
}

void searchVehicle(ParkingManager& parkingManager){
    string registrationNumber;

    cout<<"Enter registration number: ";
    cin>>registrationNumber;
    registrationNumber=toUpper(registrationNumber);
    cout<<"\n";

    Ticket* ticket=parkingManager.findVehicle(registrationNumber);
    if(ticket==nullptr){
        cout<<"Vehicle not found\n";
        return;
    }

    cout<<"Vehicle found\n";
    cout<<"Registration Number: "<<ticket->getVehicle()->getRegistrationNumber()<<"\n";
    cout<<"Vehicle Type: "<<ticket->getVehicle()->getVehicleType()<<"\n";
    cout<<"Ticket ID: "<<ticket->getTicketId()<<"\n";
    cout<<"Spot: "<<ticket->getParkingSpot()->getSpotId()<<"\n";
}

void searchTicket(ParkingManager& parkingManager){
    string ticketId;

    cout<<"Enter ticket ID: ";
    cin>>ticketId;
    ticketId=toUpper(ticketId);
    cout<<"\n";

    Ticket* ticket=parkingManager.findTicket(ticketId);
    if(ticket==nullptr){
        cout<<"Ticket not found\n";
        return;
    }

    cout<<"Ticket found\n";
    cout<<"Ticket ID: "<<ticket->getTicketId()<<"\n";
    cout<<"Vehicle: "<<ticket->getVehicle()->getRegistrationNumber()<<"\n";
    cout<<"Spot: "<<ticket->getParkingSpot()->getSpotId()<<"\n";
}

void viewParkingLot(vector<ParkingSpot*>& spots){
    cout<<"\nParking Lot:\n";
    for(ParkingSpot* spot:spots){
        cout<<spot->getSpotId()<<" - ";
        cout<<spot->getSpotType()<<" - ";

        if(spot->isOccupied()){
            cout<<"Occupied";
            if(spot->getVehicle()!=nullptr)
                cout<<" - "<<spot->getVehicle()->getRegistrationNumber();
        }
        else
            cout<<"Available";
        cout<<"\n";
    }
}

void changeParkingStrategy(ParkingManager& parkingManager, FirstAvailableSpot& firstAvailableSpot, NearestSpot& nearestSpot){
    int choice;
    cout<<"1. First Available Spot\n";
    cout<<"2. Nearest Spot\n";

    cout<<"\nEnter strategy choice: ";
    cin>>choice;
    cout<<"\n";

    if(choice==1){
        parkingManager.setParkingStrategy(&firstAvailableSpot);
        cout<<"Parking strategy changed to First Available Spot\n";
    }
    else if(choice==2){
        parkingManager.setParkingStrategy(&nearestSpot);
        cout<<"Parking strategy changed to Nearest Spot\n";
    }
    else
        cout<<"Invalid strategy choice\n";
}

void changePricingStrategy(ParkingManager& parkingManager, HourlyPrice& hourlyPrice, FlatRatePrice& flatRatePrice){
    int choice;
    cout<<"1. Hourly Pricing\n";
    cout<<"2. Flat Rate Pricing\n";

    cout<<"\nEnter pricing choice: ";
    cin>>choice;
    cout<<"\n";

    if(choice==1){
        parkingManager.setPricingStrategy(&hourlyPrice);
        cout<<"Pricing strategy changed to Hourly Pricing\n";
    }
    else if(choice==2){
        parkingManager.setPricingStrategy(&flatRatePrice);
        cout<<"Pricing strategy changed to Flat Rate Pricing\n";
    }
    else
        cout<<"Invalid pricing choice\n";
}

void viewStatistics(ParkingManager& parkingManager,vector<ParkingSpot*>& spots){
    int totalSpots=spots.size();
    int availableSpots=parkingManager.getAvailableSpotCount();
    int occupiedSpots=totalSpots-availableSpots;
    double occupancyPercentage=0;

    if(totalSpots>0)
        occupancyPercentage=(occupiedSpots*100.0)/totalSpots;

    cout<<"\nParking Statistics:\n";
    cout<<"Total Spots: "<<totalSpots<<"\n";
    cout<<"Occupied Spots: "<<occupiedSpots<<"\n";
    cout<<"Available Spots: "<<availableSpots<<"\n";
    cout<<"Occupancy: "<<occupancyPercentage<<"%\n";
}

int main(){
    Logger& logger=Logger::getInstance();
    logger.log("Parking Lot System started");

    ParkingSpot* spot1=ParkingSpotFactory::createParkingSpot("A1","Bike");
    ParkingSpot* spot2=ParkingSpotFactory::createParkingSpot("A2","Compact");
    ParkingSpot* spot3=ParkingSpotFactory::createParkingSpot("A3","Large");
    ParkingSpot* spot4=ParkingSpotFactory::createParkingSpot("A4","Electric");

    DisplayBoard displayBoard;
    spot1->addObserver(&displayBoard);
    spot2->addObserver(&displayBoard);
    spot3->addObserver(&displayBoard);
    spot4->addObserver(&displayBoard);

    vector<ParkingSpot*> spots;

    spots.push_back(spot1);
    spots.push_back(spot2);
    spots.push_back(spot3);
    spots.push_back(spot4);

    FirstAvailableSpot parkingStrategy;
    NearestSpot nearestSpot;
    HourlyPrice pricingStrategy;
    FlatRatePrice flatRatePrice;

    ParkingManager parkingManager(spots, &parkingStrategy, &pricingStrategy);
    vector<Vehicle*> vehicles;

    int choice;
    while(true){
        cout<<"\n===== Parking Lot System =====\n";
        cout<<"1. Park Vehicle\n";
        cout<<"2. Exit Vehicle\n";
        cout<<"3. View Parking Availability\n";
        cout<<"4. Search Vehicle\n";
        cout<<"5. Search Ticket\n";
        cout<<"6. View Parking Lot\n";
        cout<<"7. Change Parking Strategy\n";
        cout<<"8. Change Pricing Strategy\n";
        cout<<"9. View Statistics\n";
        cout<<"0. Exit\n";

        cout<<"\nEnter your choice: ";
        cin>>choice;
        cout<<"\n";

        if(choice==0){
            cout<<"Exiting Parking Lot System...\n";
            break;
        }
        else if(choice==1)
            parkVehicle(parkingManager, vehicles);
        else if(choice==2)
            exitVehicle(parkingManager, vehicles);
        else if(choice==3)
            viewParkingAvailability(parkingManager);
        else if(choice==4)
            searchVehicle(parkingManager);
        else if(choice==5)
            searchTicket(parkingManager);
        else if(choice==6)
            viewParkingLot(spots);
        else if(choice==7)
            changeParkingStrategy(parkingManager, parkingStrategy, nearestSpot);
        else if(choice==8)
            changePricingStrategy(parkingManager, pricingStrategy, flatRatePrice);
        else if(choice==9)
            viewStatistics(parkingManager, spots);
        else
            cout<<"Invalid choice\n";
    }

    for(ParkingSpot* spot:spots)
        delete spot;

    return 0;
}