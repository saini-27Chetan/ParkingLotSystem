#include<bits/stdc++.h>
#include"Ticket.h"
using namespace std;


Ticket::Ticket(string ticketId, Vehicle* vehicle, ParkingSpot* parkingSpot){
    this->ticketId=ticketId;
    this->vehicle=vehicle;
    this->parkingSpot=parkingSpot;
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