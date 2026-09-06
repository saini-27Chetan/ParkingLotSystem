#include<bits/stdc++.h>
#include"pricingStrategy/HourlyPrice.h"
using namespace std;

double HourlyPrice::calculatePrice(time_t entryTime, time_t exitTime){
    double duration=difftime(exitTime,entryTime);
    double hours=ceil(duration/3600.0);

    if(hours<1)
        hours=1;

    return hours*50;
}