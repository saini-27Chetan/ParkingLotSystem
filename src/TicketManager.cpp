#include<bits/stdc++.h>
#include"TicketManager.h"
using namespace std;

TicketManager::TicketManager(){
    ticketCounter=0;
}

TicketManager::~TicketManager(){
    for(Ticket* ticket:activeTickets)
        delete ticket;
}

Ticket* TicketManager::createTicket(Vehicle* vehicle, ParkingSpot* parkingSpot){
    ticketCounter++;
    string ticketId="T"+to_string(ticketCounter);

    Ticket* ticket=new Ticket(ticketId,vehicle,parkingSpot);
    activeTickets.push_back(ticket);

    return ticket;
}

Ticket* TicketManager::findTicket(string ticketId){
    for(Ticket* ticket:activeTickets){
        if(ticket->getTicketId()==ticketId)
            return ticket;
    }

    return nullptr;
}

Ticket* TicketManager::findVehicle(string registrationNumber){
    for(Ticket* ticket:activeTickets){
        if(ticket->getVehicle()->getRegistrationNumber()==registrationNumber)
            return ticket;
    }

    return nullptr;
}

void TicketManager::removeTicket(string ticketId){
    for(auto it=activeTickets.begin(); it!=activeTickets.end(); it++){
        if((*it)->getTicketId()==ticketId){
            delete *it;
            activeTickets.erase(it);
            return;
        }
    }
}