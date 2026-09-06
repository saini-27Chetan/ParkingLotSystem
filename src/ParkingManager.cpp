#include<bits/stdc++.h>
#include"ParkingManager.h"
using namespace std;

ParkingManager::ParkingManager(vector<ParkingSpot*>& spots, ParkingSpotStrategy* parkingStrategy, PricingStrategy* pricingStrategy){
    this->spots=spots;
    this->parkingStrategy=parkingStrategy;
    this->pricingStrategy=pricingStrategy;
    ticketCounter=1;
}

Ticket* ParkingManager::parkVehicle(Vehicle* vehicle){
    ParkingSpot* spot=parkingStrategy->findSpot(spots,vehicle->getVehicleType());

    if(spot==nullptr)
        return nullptr;

    if(!spot->parkVehicle(vehicle))
        return nullptr;

    string ticketId="T"+to_string(ticketCounter);
    ticketCounter++;

    Ticket* ticket=new Ticket(ticketId,vehicle,spot);
    activeTickets.push_back(ticket);

    return ticket;
}

double ParkingManager::exitVehicle(string ticketId){
    for(int i=0;i<activeTickets.size();i++){
        if(activeTickets[i]->getTicketId()==ticketId){
            Ticket* ticket=activeTickets[i];
            time_t exitTime=time(nullptr);
            double fee=pricingStrategy->calculatePrice(ticket->getEntryTime(),exitTime);

            ParkingSpot* spot=ticket->getParkingSpot();
            spot->removeVehicle();

            delete ticket;
            activeTickets.erase(activeTickets.begin()+i);

            return fee;
        }
    }

    return -1;
}

Ticket* ParkingManager::findTicket(string ticketId){
    for(Ticket* ticket:activeTickets){
        if(ticket->getTicketId()==ticketId)
            return ticket;
    }

    return nullptr;
}

int ParkingManager::getAvailableSpotCount(){
    int count=0;
    for(ParkingSpot* spot:spots){
        if(!spot->isOccupied())
            count++;
    }

    return count;
}