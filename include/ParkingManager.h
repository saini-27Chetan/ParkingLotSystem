#ifndef PARKINGMANAGER_H
#define PARKINGMANAGER_H

#include<bits/stdc++.h>
#include"Vehicle.h"
#include"ParkingSpot.h"
#include"Ticket.h"
#include"parkingStrategy/ParkingSpotStrategy.h"
using namespace std;

class ParkingManager{
    vector<ParkingSpot*> spots;
    vector<Ticket*> activeTickets;
    ParkingSpotStrategy* parkingStrategy;
    int ticketCounter;

public:
    ParkingManager(vector<ParkingSpot*>& spots, ParkingSpotStrategy* parkingStrategy);

    int getAvailableSpotCount();
    bool exitVehicle(string ticketId);
    
    Ticket* parkVehicle(Vehicle* vehicle);
    Ticket* findTicket(string ticketId);
};

#endif