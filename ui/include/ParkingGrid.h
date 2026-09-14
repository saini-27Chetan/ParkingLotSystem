#ifndef PARKINGGRID_H
#define PARKINGGRID_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollArea>

#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

class ParkingManager;
class PricingStrategy;
class ParkingSpot;

class ParkingGrid : public QWidget{
    ParkingManager* parkingManager;
    
    PricingStrategy* hourlyPricingStrategy;
    PricingStrategy* flatRatePricingStrategy;
    
    QScrollArea* scrollArea;
    QWidget* parkingWidget;
    QGridLayout* parkingGrid;
    
    unordered_map<std::string, QPushButton*> spotButtons;

public:
    ParkingGrid(ParkingManager* parkingManager, PricingStrategy* hourlyPricingStrategy, PricingStrategy* flatRatePricingStrategy, QWidget* parent = nullptr);
    void refreshSpot(const std::string& spotId);
};

#endif