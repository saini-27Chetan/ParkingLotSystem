#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "Vehicle.h"
#include "observer/ParkingObserver.h"
#include "parkingStrategy/ParkingSpotStrategy.h"
#include "pricingStrategy/PricingStrategy.h"
#include <bits/stdc++.h>
using namespace std;

class ParkingManager;
class ParkingGrid;

class MainWindow : public QMainWindow, public ParkingObserver{
    ParkingManager* parkingManager;
    ParkingGrid* parkingGrid;
    ParkingSpotStrategy* firstAvailableStrategy;
    ParkingSpotStrategy* nearestStrategy;
    PricingStrategy* hourlyPricingStrategy;
    PricingStrategy* flatRatePricingStrategy;

    vector<Vehicle*> vehicles;

    QLabel* totalLabel;
    QLabel* occupiedLabel;
    QLabel* availableLabel;

    void refreshStatistics();
    void parkVehicle();
    void exitVehicle();
    void searchVehicle();
    void searchTicket();
    void changeParkingStrategy();

    static constexpr int DIALOG_WIDTH = 300;
    static constexpr int DIALOG_HEIGHT = 200;
    static constexpr int WARNING_WIDTH = 350;
    static constexpr int WARNING_HEIGHT = 150;

public:
    MainWindow(ParkingManager* parkingManager, ParkingSpotStrategy* firstAvailableStrategy, ParkingSpotStrategy* nearestStrategy, PricingStrategy* hourlyPricingStrategy, PricingStrategy* flatRatePricingStrategy, QWidget* parent = nullptr);
    void update(string spotId, bool occupied) override;
    ~MainWindow();
};

#endif