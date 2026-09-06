#include<bits/stdc++.h>
#include"pricingStrategy/HourlyPrice.h"
#include"pricingStrategy/FlatRatePrice.h"
using namespace std;

int main(){
    time_t exitTime=time(nullptr);
    time_t entryTime=exitTime-3*3600-30*60;

    HourlyPrice hourlyPrice;
    FlatRatePrice flatRatePrice;

    double hourlyFee=hourlyPrice.calculatePrice(entryTime,exitTime);
    double flatFee=flatRatePrice.calculatePrice(entryTime,exitTime);

    cout<<"Parking Duration: 2 hours 30 minutes\n";
    cout<<"Hourly Pricing: Rs. "<<hourlyFee<<"\n";
    cout<<"Flat Rate Pricing: Rs. "<<flatFee<<"\n";

    return 0;
}