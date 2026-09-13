#include<bits/stdc++.h>
#include"Logger.h"
using namespace std;

Logger::Logger(){}

Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}

void Logger::log(string message){
    cout<<"[LOG] "<<message<<"\n";
}