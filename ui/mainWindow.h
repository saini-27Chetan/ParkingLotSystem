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
    void searchVehicle();
    void searchTicket();

    static constexpr int DIALOG_WIDTH = 300;
    static constexpr int DIALOG_HEIGHT = 200;

    static constexpr int WARNING_WIDTH = 350;
    static constexpr int WARNING_HEIGHT = 150;

public:
    MainWindow(ParkingManager* parkingManager, QWidget* parent = nullptr);
    void update(string spotId, bool occupied) override;
    ~MainWindow();
};

#endif