#ifndef PARKINGMANAGER_H
#define PARKINGMANAGER_H

#include<bits/stdc++.h>
#include"Vehicle.h"
#include"ParkingSpot.h"
#include"Ticket.h"
#include"parkingStrategy/ParkingSpotStrategy.h"
#include"pricingStrategy/PricingStrategy.h"
#include"Logger.h"
#include"TicketManager.h"
using namespace std;

class ParkingManager{
    vector<ParkingSpot*> spots;
    ParkingSpotStrategy* parkingStrategy;
    TicketManager* ticketManager;

public:
    ParkingManager(vector<ParkingSpot*>& spots, ParkingSpotStrategy* parkingStrategy);
    ~ParkingManager();

    int getAvailableSpotCount();
    double exitVehicle(string ticketId);
    void setParkingStrategy(ParkingSpotStrategy* parkingStrategy);

    vector<ParkingSpot*>& getSpots();
    
    Ticket* parkVehicle(Vehicle* vehicle, PricingStrategy* pricingStrategy);
    Ticket* findTicket(string ticketId);
    Ticket* findVehicle(string registrationNumber);
};

#endif