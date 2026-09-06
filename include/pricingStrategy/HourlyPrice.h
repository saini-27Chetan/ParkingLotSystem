#ifndef HOURLYPRICE_H
#define HOURLYPRICE_H

#include<bits/stdc++.h>
#include"PricingStrategy.h"
using namespace std;

class HourlyPrice:public PricingStrategy{
public:
    double calculatePrice(time_t entryTime, time_t exitTime) override;
};

#endif