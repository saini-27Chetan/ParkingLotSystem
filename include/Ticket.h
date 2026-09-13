#ifndef TICKET_H
#define TICKET_H

#include<bits/stdc++.h>
#include"Vehicle.h"
#include"ParkingSpot.h"
#include"pricingStrategy/PricingStrategy.h"
using namespace std;

class Ticket{
    string ticketId;
    Vehicle* vehicle;
    ParkingSpot* parkingSpot;
    time_t entryTime;
    PricingStrategy* pricingStrategy;

public:
    Ticket(string ticketId,Vehicle* vehicle, ParkingSpot* parkingSpot, PricingStrategy* pricingStrategy);

    string getTicketId();
    Vehicle* getVehicle();
    ParkingSpot* getParkingSpot();
    PricingStrategy* getPricingStrategy();
    time_t getEntryTime();
};

#endif