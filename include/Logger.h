#ifndef LOGGER_H
#define LOGGER_H

#include<bits/stdc++.h>
using namespace std;

class Logger{
    Logger();

public:
    static Logger& getInstance();
    void log(string message);
};

#endif