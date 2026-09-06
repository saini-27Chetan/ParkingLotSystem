#include<bits/stdc++.h>
#include"Vehicle.h"
using namespace std;

int main(){
    Vehicle vehicle("HR26AB1234","Car");

    cout<<"Registration Number: "<<vehicle.getRegistrationNumber()<<"\n";
    cout<<"Vehicle Type: "<<vehicle.getVehicleType()<<"\n";

    return 0;
}