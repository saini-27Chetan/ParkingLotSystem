#include "MainWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>
#include "ParkingManager.h"
#include "ParkingSpot.h"
#include "VehicleFactory.h"
using namespace std;

void MainWindow::refreshStatistics(){
    int totalSpots = parkingManager->getSpots().size();
    int availableSpots = parkingManager->getAvailableSpotCount();
    int occupiedSpots = totalSpots - availableSpots;

    totalLabel->setText("Total Spots\n" + QString::number(totalSpots));
    occupiedLabel->setText("Occupied\n" + QString::number(occupiedSpots));
    availableLabel->setText("Available\n" + QString::number(availableSpots));
}

void MainWindow::refreshSpot(std::string spotId){
    auto buttonIterator = spotButtons.find(spotId);
    if(buttonIterator == spotButtons.end())
        return;

    QPushButton* button = buttonIterator->second;
    for(ParkingSpot* spot : parkingManager->getSpots()){
        if(spot->getSpotId() != spotId)
            continue;

        QString text = QString::fromStdString(spot->getSpotId());
        text += "\n";
        text += QString::fromStdString(spot->getSpotType());
        text += "\n";

        if(spot->isOccupied()){
            text += "OCCUPIED";
            if(spot->getVehicle() != nullptr){
                text += "\n";
                text += QString::fromStdString(spot->getVehicle()->getRegistrationNumber());
                Ticket* ticket = parkingManager->findVehicle(spot->getVehicle()->getRegistrationNumber());

                if(ticket != nullptr){
                    text += "\nTicket ID: ";
                    text += QString::fromStdString(ticket->getTicketId());
                }
            }
        }
        else
            text += "AVAILABLE";

        button->setText(text);
        break;
    }
}

void MainWindow::parkVehicle(){
    bool ok;
    QString registrationNumber = QInputDialog::getText(this, "Park Vehicle", "Enter registration number:", QLineEdit::Normal, "", &ok);

    if(!ok)
        return;

    registrationNumber = registrationNumber.trimmed().toUpper();
    if(registrationNumber.isEmpty()){
        QMessageBox::warning(
            this, "Invalid Input", "Registration number cannot be empty.");
        return;
    }

    QStringList vehicleTypes;
    vehicleTypes << "CAR"
                 << "BIKE"
                 << "ELECTRIC";

    QString vehicleType = QInputDialog::getItem(this, "Park Vehicle", "Select vehicle type:", vehicleTypes, 0, false, &ok);

    if(!ok)
        return;

    string regNumber = registrationNumber.toStdString();
    string type = vehicleType.toStdString();
    if(parkingManager->findVehicle(regNumber) != nullptr){
        QMessageBox::warning(this, "Vehicle Already Parked", "This vehicle is already parked.");
        return;
    }

    Vehicle* vehicle = VehicleFactory::createVehicle(regNumber, type);
    Ticket* ticket = parkingManager->parkVehicle(vehicle);
    if(ticket == nullptr){
        delete vehicle;
        QMessageBox::warning(this, "Parking Unavailable", "No suitable parking spot is available.");
        return;
    }

    vehicles.push_back(vehicle);
    refreshSpot(ticket->getParkingSpot()->getSpotId());
    QMessageBox::information(this, "Vehicle Parked", "Vehicle parked successfully.\n\n" "Ticket ID: " + QString::fromStdString(ticket->getTicketId()) + "\nSpot: " +QString::fromStdString(ticket->getParkingSpot()->getSpotId()));
}

void MainWindow::exitVehicle(){
    bool ok;
    QString ticketId = QInputDialog::getText(this, "Exit Vehicle", "Enter ticket ID:", QLineEdit::Normal, "", &ok);

    if(!ok)
        return;

    ticketId = ticketId.trimmed().toUpper();
    if(ticketId.isEmpty()){
        QMessageBox::warning(this, "Invalid Input", "Ticket ID cannot be empty.");
        return;
    }

    string id = ticketId.toStdString();
    Ticket* ticket = parkingManager->findTicket(id);
    if(ticket == nullptr){
        QMessageBox::warning(this, "Invalid Ticket", "Invalid ticket ID.");
        return;
    }

    Vehicle* vehicle = ticket->getVehicle();
    double fee = parkingManager->exitVehicle(id);

    if(fee == -1){
        QMessageBox::warning(this, "Invalid Ticket", "Invalid ticket ID.");
        return;
    }

    for(auto it = vehicles.begin(); it != vehicles.end(); ++it){
        if(*it == vehicle){
            delete *it;
            vehicles.erase(it);
            break;
        }
    }

    QMessageBox::information( this, "Vehicle Exited", "Vehicle exited successfully.\n\n" "Ticket ID: " + ticketId + "\nParking Fee: Rs. " + QString::number(fee, 'f', 2)
    );
}

MainWindow::MainWindow(ParkingManager* parkingManager, QWidget* parent) : QMainWindow(parent){
    this->parkingManager = parkingManager;

    setWindowTitle("Parking Lot System");
    resize(1000, 700);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QLabel* title = new QLabel("PARKING LOT SYSTEM");
    title->setAlignment(Qt::AlignCenter);

    totalLabel = new QLabel();
    occupiedLabel = new QLabel();
    availableLabel = new QLabel();

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
        string spotId = spot->getSpotId();
        QString spotType = QString::fromStdString(spot->getSpotType());
        QString status;

        if(spot->isOccupied()){
            status = "OCCUPIED";
            if(spot->getVehicle() != nullptr){
                status += "\n" + QString::fromStdString(spot->getVehicle()->getRegistrationNumber());
                Ticket* ticket = parkingManager->findVehicle(spot->getVehicle()->getRegistrationNumber());

                if(ticket != nullptr){
                    status += "\nTicket ID: ";
                    status += QString::fromStdString(
                        ticket->getTicketId()
                    );
                }
            }
        }
        else
            status = "AVAILABLE";

        QString buttonText = QString::fromStdString(spotId) + "\n" + spotType + "\n" + status;
        QPushButton* spotButton = new QPushButton(buttonText);
        spotButton->setMinimumSize(150, 90);
        parkingGrid->addWidget(spotButton, row, column);
        spotButtons[spotId] = spotButton;
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
    
    connect(parkButton, &QPushButton::clicked, this, &MainWindow::parkVehicle);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitVehicle);

    buttonLayout->addWidget(parkButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addWidget(searchButton);

    mainLayout->addWidget(title);
    mainLayout->addLayout(statsLayout);
    mainLayout->addWidget(parkingAreaTitle);
    mainLayout->addLayout(parkingGrid);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    for(ParkingSpot* spot : parkingManager->getSpots())
        spot->addObserver(this);

    refreshStatistics();
}

void MainWindow::update(string spotId, bool occupied){
    refreshSpot(spotId);
    refreshStatistics();
}

MainWindow::~MainWindow(){
    for(Vehicle* vehicle : vehicles)
        delete vehicle;
}