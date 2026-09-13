#include "MainWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "ParkingManager.h"
#include "ParkingSpot.h"

MainWindow::MainWindow(ParkingManager* parkingManager,QWidget* parent){
    this->parkingManager=parkingManager;

    setWindowTitle("Parking Lot System");
    resize(1000, 700);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QLabel *title = new QLabel("PARKING LOT SYSTEM");
    title->setAlignment(Qt::AlignCenter);

    QHBoxLayout *statsLayout = new QHBoxLayout();

    int totalSpots = parkingManager->getSpots().size();
    int availableSpots = parkingManager->getAvailableSpotCount();
    int occupiedSpots = totalSpots - availableSpots;

    QLabel* totalLabel = new QLabel(
        "Total Spots\n" + QString::number(totalSpots)
    );

    QLabel* occupiedLabel = new QLabel(
        "Occupied\n" + QString::number(occupiedSpots)
    );

    QLabel* availableLabel = new QLabel(
        "Available\n" + QString::number(availableSpots)
    );

    totalLabel->setAlignment(Qt::AlignCenter);
    occupiedLabel->setAlignment(Qt::AlignCenter);
    availableLabel->setAlignment(Qt::AlignCenter);

    statsLayout->addWidget(totalLabel);
    statsLayout->addWidget(occupiedLabel);
    statsLayout->addWidget(availableLabel);

    QLabel* parkingArea = new QLabel();
    QString parkingText = "PARKING AREA\n\n";

    for(ParkingSpot* spot : parkingManager->getSpots()){
        parkingText += QString::fromStdString(spot->getSpotId());
        parkingText += " - ";
        parkingText += QString::fromStdString(spot->getSpotType());

        if(spot->isOccupied()){
            parkingText += " - OCCUPIED";
            if(spot->getVehicle() != nullptr){
                parkingText += " - ";
                parkingText += QString::fromStdString(spot->getVehicle()->getRegistrationNumber());
            }
        }
        else
            parkingText += " - AVAILABLE";
        parkingText += "\n";
    }

    parkingArea->setText(parkingText);
    parkingArea->setAlignment(Qt::AlignCenter);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *parkButton = new QPushButton("Park Vehicle");
    QPushButton *exitButton = new QPushButton("Exit Vehicle");
    QPushButton *searchButton = new QPushButton("Search");

    buttonLayout->addWidget(parkButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addWidget(searchButton);

    mainLayout->addWidget(title);
    mainLayout->addLayout(statsLayout);
    mainLayout->addWidget(parkingArea);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}