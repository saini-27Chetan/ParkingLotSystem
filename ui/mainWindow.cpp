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
    QInputDialog dialog(this);
    dialog.setWindowTitle("Park Vehicle");
    dialog.setLabelText("Enter registration number:");
    dialog.setInputMode(QInputDialog::TextInput);
    dialog.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    if(dialog.exec() != QDialog::Accepted)
        return;

    QString registrationNumber = dialog.textValue();
    registrationNumber = registrationNumber.trimmed().toUpper();
    if(registrationNumber.isEmpty()){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Invalid Input");
        messageBox.setText("Registration number cannot be empty.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    QStringList vehicleTypes;
    vehicleTypes << "CAR"
                 << "BIKE"
                 << "ELECTRIC";

    QInputDialog vehicleTypeDialog(this);
    vehicleTypeDialog.setWindowTitle("Park Vehicle");
    vehicleTypeDialog.setLabelText("Select vehicle type:");
    vehicleTypeDialog.setComboBoxItems(vehicleTypes);
    vehicleTypeDialog.setComboBoxEditable(false);
    vehicleTypeDialog.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    if(vehicleTypeDialog.exec() != QDialog::Accepted)
        return;

    QString vehicleType = vehicleTypeDialog.textValue();
    string regNumber = registrationNumber.toStdString();
    string type = vehicleType.toStdString();
    QStringList pricingOptions;
    pricingOptions << "Hourly Pricing"
                   << "Flat Rate Pricing";

    QInputDialog pricingDialog(this);
    pricingDialog.setWindowTitle("Park Vehicle");
    pricingDialog.setLabelText("Select pricing strategy:");
    pricingDialog.setComboBoxItems(pricingOptions);
    pricingDialog.setComboBoxEditable(false);
    pricingDialog.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    if(pricingDialog.exec() != QDialog::Accepted)
        return;

    QString pricingChoice = pricingDialog.textValue();
    PricingStrategy* pricingStrategy = nullptr;
    if(pricingChoice == "Hourly Pricing")
        pricingStrategy = hourlyPricingStrategy;
    else if(pricingChoice == "Flat Rate Pricing")
        pricingStrategy = flatRatePricingStrategy;

    if(parkingManager->findVehicle(regNumber) != nullptr){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Vehicle Already Parked");
        messageBox.setText("This vehicle is already parked.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    Vehicle* vehicle = VehicleFactory::createVehicle(regNumber, type);
    Ticket* ticket = parkingManager->parkVehicle(vehicle,pricingStrategy);
    if(ticket == nullptr){
        delete vehicle;
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Parking Unavailable");
        messageBox.setText("No suitable parking spot is available.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    vehicles.push_back(vehicle);
    refreshSpot(ticket->getParkingSpot()->getSpotId());
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Vehicle Parked");
    messageBox.setText("Vehicle parked successfully.\n\n" "Ticket ID: " + QString::fromStdString(ticket->getTicketId()) + "\nSpot: " + QString::fromStdString(ticket->getParkingSpot()->getSpotId()) );
    messageBox.setIcon(QMessageBox::Information);
    messageBox.resize(DIALOG_WIDTH, DIALOG_HEIGHT);
    messageBox.exec();
}

void MainWindow::exitVehicle(){
    QInputDialog dialog(this);
    dialog.setWindowTitle("Exit Vehicle");
    dialog.setLabelText("Enter ticket ID:");
    dialog.setInputMode(QInputDialog::TextInput);
    dialog.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    if(dialog.exec() != QDialog::Accepted)
        return;

    QString ticketId = dialog.textValue();
    ticketId = ticketId.trimmed().toUpper();
    if(ticketId.isEmpty()){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Invalid Input");
        messageBox.setText("Ticket ID cannot be empty.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    string id = ticketId.toStdString();
    Ticket* ticket = parkingManager->findTicket(id);
    if(ticket == nullptr){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Invalid Ticket");
        messageBox.setText("Invalid ticket ID.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    Vehicle* vehicle = ticket->getVehicle();
    double fee = parkingManager->exitVehicle(id);
    if(fee == -1){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Invalid Ticket");
        messageBox.setText("Invalid ticket ID.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    for(auto it = vehicles.begin(); it != vehicles.end(); ++it){
        if(*it == vehicle){
            delete *it;
            vehicles.erase(it);
            break;
        }
    }

    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Vehicle Exited");
    messageBox.setText("Vehicle exited successfully.\n\n" "Ticket ID: " + ticketId + "\nParking Fee: Rs. " + QString::number(fee, 'f', 2) );
    messageBox.setIcon(QMessageBox::Information);
    messageBox.resize(DIALOG_WIDTH, DIALOG_HEIGHT);
    messageBox.exec();
}

void MainWindow::searchVehicle(){
    QInputDialog dialog(this);
    dialog.setWindowTitle("Search Vehicle");
    dialog.setLabelText("Enter registration number:");
    dialog.setInputMode(QInputDialog::TextInput);
    dialog.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    if(dialog.exec() != QDialog::Accepted)
        return;

    QString registrationNumber = dialog.textValue();
    registrationNumber = registrationNumber.trimmed().toUpper();
    if(registrationNumber.isEmpty()){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Invalid Input");
        messageBox.setText("Registration number cannot be empty.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    string regNumber = registrationNumber.toStdString();
    Ticket* ticket = parkingManager->findVehicle(regNumber);
    if(ticket == nullptr){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Vehicle Not Found");
        messageBox.setText("Vehicle not found.");
        messageBox.setIcon(QMessageBox::Information);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    QString message;
    message += "Vehicle found\n\n";
    message += "Registration Number: ";
    message += QString::fromStdString(ticket->getVehicle()->getRegistrationNumber());

    message += "\nVehicle Type: ";
    message += QString::fromStdString(ticket->getVehicle()->getVehicleType());

    message += "\nTicket ID: ";
    message += QString::fromStdString(ticket->getTicketId());

    message += "\nSpot: ";
    message += QString::fromStdString(ticket->getParkingSpot()->getSpotId());

    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Vehicle Found");
    messageBox.setText(message);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.resize(DIALOG_WIDTH, DIALOG_HEIGHT);
    messageBox.exec();
}

void MainWindow::searchTicket(){
    QInputDialog dialog(this);
    dialog.setWindowTitle("Search Vehicle by Ticket Id");
    dialog.setLabelText("Enter ticket ID:");
    dialog.setInputMode(QInputDialog::TextInput);
    dialog.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    if(dialog.exec() != QDialog::Accepted)
        return;

    QString ticketId = dialog.textValue();
    ticketId = ticketId.trimmed().toUpper();
    if(ticketId.isEmpty()){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Invalid Input");
        messageBox.setText("Ticket ID cannot be empty.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    string id = ticketId.toStdString();
    Ticket* ticket = parkingManager->findTicket(id);
    if(ticket == nullptr){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Ticket Not Found");
        messageBox.setText("Ticket not found.");
        messageBox.setIcon(QMessageBox::Information);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

    QString message;
    message += "Ticket found\n\n";
    message += "Registration Number: ";
    message += QString::fromStdString(ticket->getVehicle()->getRegistrationNumber());

    message += "\nVehicle Type: ";
    message += QString::fromStdString(ticket->getVehicle()->getVehicleType());

    message += "\nTicket ID: ";
    message += QString::fromStdString(ticket->getTicketId());

    message += "\nSpot: ";
    message += QString::fromStdString(ticket->getParkingSpot()->getSpotId());

    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Ticket Found");
    messageBox.setText(message);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.resize(DIALOG_WIDTH, DIALOG_HEIGHT);
    messageBox.exec();
}

void MainWindow::changeParkingStrategy(){
    QStringList options;
    options << "First Available Spot"
            << "Nearest Available Spot";

    QInputDialog dialog(this);
    dialog.setWindowTitle("Change Parking Strategy");
    dialog.setLabelText("Select parking strategy:");
    dialog.setInputMode(QInputDialog::TextInput);
    dialog.setComboBoxItems(options);
    dialog.setComboBoxEditable(false);
    dialog.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    if(dialog.exec() != QDialog::Accepted)
        return;

    QString choice = dialog.textValue();
    if(choice == "First Available Spot"){
        parkingManager->setParkingStrategy(firstAvailableStrategy);
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Parking Strategy Changed");
        messageBox.setText("Parking strategy changed to First Available Spot.");
        messageBox.setIcon(QMessageBox::Information);
        messageBox.resize(DIALOG_WIDTH, DIALOG_HEIGHT);
        messageBox.exec();
    }

    else if(choice == "Nearest Available Spot"){
        parkingManager->setParkingStrategy(nearestStrategy);
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Parking Strategy Changed");
        messageBox.setText("Parking strategy changed to Nearest Available Spot.");
        messageBox.setIcon(QMessageBox::Information);
        messageBox.resize(DIALOG_WIDTH, DIALOG_HEIGHT);
        messageBox.exec();
    }
}

MainWindow::MainWindow(ParkingManager* parkingManager, ParkingSpotStrategy* firstAvailableStrategy, ParkingSpotStrategy* nearestStrategy, PricingStrategy* hourlyPricingStrategy, PricingStrategy* flatRatePricingStrategy, QWidget* parent) : QMainWindow(parent){
    this->parkingManager = parkingManager;
    this->firstAvailableStrategy = firstAvailableStrategy;
    this->nearestStrategy = nearestStrategy;
    this->hourlyPricingStrategy = hourlyPricingStrategy;
    this->flatRatePricingStrategy = flatRatePricingStrategy;

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

        QString buttonText =QString::fromStdString(spotId) + "\n" + spotType + "\n" + status;
        QPushButton* spotButton = new QPushButton(buttonText);
        spotButton->setMinimumSize(150, 90);
        parkingGrid->addWidget(spotButton, row, column );
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
    QPushButton* strategyButton = new QPushButton("Change Parking Strategy");

    connect(parkButton, &QPushButton::clicked, this, &MainWindow::parkVehicle );
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitVehicle );
    connect(strategyButton, &QPushButton::clicked, this, &MainWindow::changeParkingStrategy);
    connect(searchButton, &QPushButton::clicked, this, [this](){
        QStringList options;
        options << "Search Vehicle by Registration Number"
                << "Search Vehicle by Ticket Id";

        QInputDialog dialog(this);
        dialog.setWindowTitle("Search");
        dialog.setLabelText("Select search type:");
        dialog.setInputMode(QInputDialog::TextInput);
        dialog.setComboBoxItems(options);
        dialog.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

        if(dialog.exec() != QDialog::Accepted)
            return;

        QString choice = dialog.textValue();
        if(choice == "Search Vehicle by Registration Number")
            searchVehicle();
        else if(choice == "Search Vehicle by Ticket Id")
            searchTicket();
    });

    buttonLayout->addWidget(parkButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(strategyButton);

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