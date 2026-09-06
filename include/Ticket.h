#ifndef TICKET_H
#define TICKET_H

#include<bits/stdc++.h>
#include"Vehicle.h"
#include"ParkingSpot.h"
using namespace std;

class Ticket{
    string ticketId;
    Vehicle* vehicle;
    ParkingSpot* parkingSpot;
    time_t entryTime;

public:
    Ticket(string ticketId,Vehicle* vehicle, ParkingSpot* parkingSpot);

    string getTicketId();
    Vehicle* getVehicle();
    ParkingSpot* getParkingSpot();
    time_t getEntryTime();
};

#endif