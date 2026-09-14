#include<bits/stdc++.h>
#include"ParkingManager.h"
using namespace std;

ParkingManager::ParkingManager(vector<ParkingSpot*>& spots, ParkingSpotStrategy* parkingStrategy){
    this->spots=spots;
    this->parkingStrategy=parkingStrategy;
    this->ticketManager=new TicketManager();
}

void ParkingManager::setParkingStrategy(ParkingSpotStrategy* parkingStrategy){
    this->parkingStrategy=parkingStrategy;
}

Ticket* ParkingManager::parkVehicle(Vehicle* vehicle, PricingStrategy* pricingStrategy){
    ParkingSpot* spot=parkingStrategy->findSpot(spots,vehicle->getVehicleType());

    if(spot==nullptr)
        return nullptr;

    if(!spot->parkVehicle(vehicle))
        return nullptr;

    Ticket* ticket=ticketManager->createTicket(vehicle,spot,pricingStrategy);
    Logger::getInstance().log("Vehicle parked: "+vehicle->getRegistrationNumber());

    return ticket;
}

double ParkingManager::exitVehicle(string ticketId){
    Ticket* ticket=ticketManager->findTicket(ticketId);

    if(ticket==nullptr)
        return -1;

    time_t exitTime=time(nullptr);
    double fee=ticket->getPricingStrategy()->calculatePrice(ticket->getEntryTime(), exitTime);

    ParkingSpot* spot=ticket->getParkingSpot();

    string registrationNumber=ticket->getVehicle()->getRegistrationNumber();
    spot->removeVehicle();
    ticketManager->removeTicket(ticketId);
    Logger::getInstance().log("Vehicle exited: "+registrationNumber);

    return fee;
}

Ticket* ParkingManager::findTicket(string ticketId){
    return ticketManager->findTicket(ticketId);
}

Ticket* ParkingManager::findVehicle(string registrationNumber){
    return ticketManager->findVehicle(registrationNumber);
}

vector<ParkingSpot*>& ParkingManager::getSpots(){
    return spots;
}

int ParkingManager::getAvailableSpotCount(){
    int count=0;
    for(ParkingSpot* spot:spots){
        if(!spot->isOccupied())
            count++;
    }

    return count;
}

ParkingManager::~ParkingManager(){
    delete ticketManager;
}