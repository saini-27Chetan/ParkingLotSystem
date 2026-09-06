#ifndef PRICINGSTRATEGY_H
#define PRICINGSTRATEGY_H

#include<bits/stdc++.h>
using namespace std;

class PricingStrategy{
public:
    virtual double calculatePrice(time_t entryTime, time_t exitTime)=0;
    virtual ~PricingStrategy(){}
};

#endif