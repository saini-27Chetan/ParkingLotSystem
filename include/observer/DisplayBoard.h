#ifndef DISPLAYBOARD_H
#define DISPLAYBOARD_H

#include<bits/stdc++.h>
#include"ParkingObserver.h"
using namespace std;

class DisplayBoard:public ParkingObserver{
public:
    void update(string spotId, bool occupied) override;
};

#endif