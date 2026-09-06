#ifndef FLATRATEPRICE_H
#define FLATRATEPRICE_H

#include<bits/stdc++.h>
#include"PricingStrategy.h"
using namespace std;

class FlatRatePrice:public PricingStrategy{
public:
    double calculatePrice(time_t entryTime, time_t exitTime) override;
};

#endif