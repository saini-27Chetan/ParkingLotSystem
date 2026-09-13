#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ParkingManager;

class MainWindow : public QMainWindow{
    ParkingManager* parkingManager;
public:
    MainWindow(ParkingManager* parkingManager, QWidget* parent=nullptr);
};

#endif