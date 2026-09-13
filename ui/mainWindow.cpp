#include "MainWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include "ParkingManager.h"
#include "ParkingSpot.h"

MainWindow::MainWindow(ParkingManager* parkingManager, QWidget* parent) : QMainWindow(parent){
    this->parkingManager = parkingManager;

    setWindowTitle("Parking Lot System");
    resize(1000, 700);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QLabel* title = new QLabel("PARKING LOT SYSTEM");
    title->setAlignment(Qt::AlignCenter);

    int totalSpots = parkingManager->getSpots().size();
    int availableSpots = parkingManager->getAvailableSpotCount();
    int occupiedSpots = totalSpots - availableSpots;

    QLabel* totalLabel = new QLabel("Total Spots\n" + QString::number(totalSpots));
    QLabel* occupiedLabel = new QLabel("Occupied\n" + QString::number(occupiedSpots));
    QLabel* availableLabel = new QLabel("Available\n" + QString::number(availableSpots));

    totalLabel->setAlignment(Qt::AlignCenter);
    occupiedLabel->setAlignment(Qt::AlignCenter);
    availableLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout* statsLayout = new QHBoxLayout();

    statsLayout->addWidget(totalLabel);
    statsLayout->addWidget(occupiedLabel);
    statsLayout->addWidget(availableLabel);

    QLabel* parkingAreaTitle = new QLabel("PARKING AREA");
    parkingAreaTitle->setAlignment(Qt::AlignCenter);
    QGridLayout* parkingGrid = new QGridLayout();

    int row = 0, column = 0;
    for(ParkingSpot* spot : parkingManager->getSpots()){
        QString spotId = QString::fromStdString(spot->getSpotId());
        QString spotType = QString::fromStdString(spot->getSpotType());
        QString status;

        if(spot->isOccupied()){
            status = "OCCUPIED";
            if(spot->getVehicle() != nullptr)
                status += "\n" + QString::fromStdString(spot->getVehicle()->getRegistrationNumber());
        }
        else
            status = "AVAILABLE";

        QString buttonText = spotId + "\n" + spotType + "\n" + status;
        QPushButton* spotButton = new QPushButton(buttonText);
        spotButton->setMinimumSize(150, 90);

        parkingGrid->addWidget(spotButton, row, column);
        column++;

        if(column == 4){
            column = 0;
            row++;
        }
    }

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* parkButton = new QPushButton("Park Vehicle");
    QPushButton* exitButton = new QPushButton("Exit Vehicle");
    QPushButton* searchButton = new QPushButton("Search");

    buttonLayout->addWidget(parkButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addWidget(searchButton);

    mainLayout->addWidget(title);
    mainLayout->addLayout(statsLayout);
    mainLayout->addWidget(parkingAreaTitle);
    mainLayout->addLayout(parkingGrid);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}