#include<bits/stdc++.h>
#include"Ticket.h"
using namespace std;


Ticket::Ticket(string ticketId, Vehicle* vehicle, ParkingSpot* parkingSpot, PricingStrategy* pricingStrategy){
    this->ticketId=ticketId;
    this->vehicle=vehicle;
    this->parkingSpot=parkingSpot;
    this->pricingStrategy = pricingStrategy;
    entryTime=time(nullptr);
}

string Ticket::getTicketId(){
    return ticketId;
}

Vehicle* Ticket::getVehicle(){
    return vehicle;
}

ParkingSpot* Ticket::getParkingSpot(){
    return parkingSpot;
}

time_t Ticket::getEntryTime(){
    return entryTime;
}

PricingStrategy* Ticket::getPricingStrategy(){
    return pricingStrategy;
}