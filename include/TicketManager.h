#ifndef TICKETMANAGER_H
#define TICKETMANAGER_H

#include<bits/stdc++.h>
#include"Ticket.h"
using namespace std;

class TicketManager{
    vector<Ticket*> activeTickets;
    int ticketCounter;

public:
    TicketManager();
    ~TicketManager();

    Ticket* createTicket(Vehicle* vehicle,ParkingSpot* parkingSpot);
    Ticket* findTicket(string ticketId);
    Ticket* findVehicle(string registrationNumber);
    void removeTicket(string ticketId);
};

#endif