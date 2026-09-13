#include<bits/stdc++.h>
#include"observer/DisplayBoard.h"
using namespace std;

void DisplayBoard::update(string spotId, bool occupied){
    cout<<"\nDisplay Board Update: ";
    cout<<spotId<<" is ";

    occupied? cout<<"Occupied\n": cout<<"Available\n";
}