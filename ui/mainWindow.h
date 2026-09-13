#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "Vehicle.h"
#include "observer/ParkingObserver.h"
#include <bits/stdc++.h>
using namespace std;

class ParkingManager;

class MainWindow : public QMainWindow, public ParkingObserver{
    ParkingManager* parkingManager;
    map<string, QPushButton*> spotButtons;
    vector<Vehicle*> vehicles;

    QLabel* totalLabel;
    QLabel* occupiedLabel;
    QLabel* availableLabel;

    void refreshStatistics();
    void refreshSpot(std::string spotId);
    void parkVehicle();
    void exitVehicle();

public:
    MainWindow(ParkingManager* parkingManager, QWidget* parent = nullptr);
    void update(string spotId, bool occupied) override;
    ~MainWindow();
};

#endif