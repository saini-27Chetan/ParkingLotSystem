#ifndef PARKINGOBSERVER_H
#define PARKINGOBSERVER_H

#include<bits/stdc++.h>
using namespace std;

class ParkingObserver{
public:
    virtual void update(string spotId, bool occupied)=0;
    virtual ~ParkingObserver(){}
};

#endif