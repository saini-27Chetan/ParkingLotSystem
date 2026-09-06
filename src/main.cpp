#include<bits/stdc++.h>
#include"VehicleFactory.h"
using namespace std;


int main(){
    Vehicle* vehicle=VehicleFactory::createVehicle("HR26AB1234","Car");

    cout<<"Registration Number: "<<vehicle->getRegistrationNumber()<<"\n";
    cout<<"Vehicle Type: "<<vehicle->getVehicleType()<<"\n";

    delete vehicle;

    return 0;
}