#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QDialog>

#include "MainWindow.h"
#include "ParkingGrid.h"
#include "ParkingManager.h"
#include "VehicleFactory.h"
#include "dialogs/ParkDialog.h"
#include "dialogs/ExitDialog.h"
using namespace std;

void MainWindow::refreshStatistics(){
    int totalSpots = parkingManager->getSpots().size();
    int availableSpots = parkingManager->getAvailableSpotCount();
    int occupiedSpots = totalSpots - availableSpots;

    totalLabel->setText("Total Spots\n" + QString::number(totalSpots));
    occupiedLabel->setText("Occupied\n" + QString::number(occupiedSpots));
    availableLabel->setText("Available\n" + QString::number(availableSpots));
}

void MainWindow::parkVehicle(){
    ParkDialog dialog(this);

    if(dialog.exec() != QDialog::Accepted)
        return;

    string regNumber = dialog.getRegistrationNumber();
    string type = dialog.getVehicleType();
    string pricingChoice = dialog.getPricingType();

    if(regNumber.empty()){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Invalid Input");
        messageBox.setText("Registration number cannot be empty.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

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
    Ticket* ticket = parkingManager->parkVehicle(vehicle, pricingStrategy );

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

    QString pricingText;
    if(ticket->getPricingStrategy() == hourlyPricingStrategy)
        pricingText = "Hourly";
    else if(ticket->getPricingStrategy() == flatRatePricingStrategy)
        pricingText = "Flat Rate";

    vehicles.push_back(vehicle);
    parkingGrid->refreshSpot(ticket->getParkingSpot()->getSpotId());
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Vehicle Parked");
    messageBox.setText("Vehicle parked successfully.\n\n" "Ticket ID: " + QString::fromStdString(ticket->getTicketId()) + "\nPricing Strategy: " + pricingText + "\nSpot: " + QString::fromStdString(ticket->getParkingSpot()->getSpotId()));
    messageBox.setIcon(QMessageBox::Information);
    messageBox.resize(DIALOG_WIDTH, DIALOG_HEIGHT);
    messageBox.exec();
}

void MainWindow::exitVehicle(){
    ExitDialog dialog(this);

    if(dialog.exec() != QDialog::Accepted)
        return;

    string id = dialog.getTicketId();
    if(id.empty()){
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Invalid Input");
        messageBox.setText("Ticket ID cannot be empty.");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.resize(WARNING_WIDTH, WARNING_HEIGHT);
        messageBox.exec();
        return;
    }

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

    QMessageBox confirmationBox(this);
    confirmationBox.setWindowTitle("Confirm Exit");
    confirmationBox.setText("Are you sure you want to exit this vehicle?");
    confirmationBox.setIcon(QMessageBox::Question);
    confirmationBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmationBox.setDefaultButton(QMessageBox::No);
    confirmationBox.resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    if(confirmationBox.exec() != QMessageBox::Yes)
        return;

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
    messageBox.setText("Vehicle exited successfully.\n\n" "Ticket ID: " + QString::fromStdString(id) + "\nParking Fee: Rs. " + QString::number(fee, 'f', 2) );
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

    message += "\nPricing Strategy: ";
    if(ticket->getPricingStrategy() == hourlyPricingStrategy)
        message += "Hourly";
    else if(ticket->getPricingStrategy() == flatRatePricingStrategy)
        message += "Flat Rate";

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

    message += "\nPricing Strategy: ";
    if(ticket->getPricingStrategy() == hourlyPricingStrategy)
        message += "Hourly";
    else if(ticket->getPricingStrategy() == flatRatePricingStrategy)
        message += "Flat Rate";

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
    this->parkingGrid = new ParkingGrid(this->parkingManager, this->hourlyPricingStrategy, this->flatRatePricingStrategy, this);

    setWindowTitle("Parking Lot System");
    resize(1000, 700);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);

    QLabel* title = new QLabel("PARKING LOT SYSTEM");
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont;
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    title->setFont(titleFont);

    totalLabel = new QLabel();
    occupiedLabel = new QLabel();
    availableLabel = new QLabel();

    totalLabel->setAlignment(Qt::AlignCenter);
    occupiedLabel->setAlignment(Qt::AlignCenter);
    availableLabel->setAlignment(Qt::AlignCenter);

    QFont statsFont;
    statsFont.setPointSize(13);
    statsFont.setBold(true);
    totalLabel->setFont(statsFont);
    occupiedLabel->setFont(statsFont);
    availableLabel->setFont(statsFont);

    QHBoxLayout* statsLayout = new QHBoxLayout();

    statsLayout->addWidget(totalLabel);
    statsLayout->addWidget(occupiedLabel);
    statsLayout->addWidget(availableLabel);

    QLabel* parkingAreaTitle = new QLabel("PARKING AREA");
    parkingAreaTitle->setAlignment(Qt::AlignCenter);
    QFont parkingAreaFont;
    parkingAreaFont.setPointSize(14);
    parkingAreaFont.setBold(true);
    parkingAreaTitle->setFont(parkingAreaFont);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* parkButton = new QPushButton("Park Vehicle");
    QPushButton* exitButton = new QPushButton("Exit Vehicle");
    QPushButton* searchButton = new QPushButton("Search");
    QPushButton* strategyButton = new QPushButton("Change Parking Strategy");

    QFont buttonFont;
    buttonFont.setPointSize(11);
    buttonFont.setBold(true);

    parkButton->setFont(buttonFont);
    exitButton->setFont(buttonFont);
    searchButton->setFont(buttonFont);
    strategyButton->setFont(buttonFont);

    // parkButton->setMinimumHeight(42);
    // exitButton->setMinimumHeight(42);
    // searchButton->setMinimumHeight(42);
    // strategyButton->setMinimumHeight(42);

    parkButton->setFixedHeight(42);
    exitButton->setFixedHeight(42);
    searchButton->setFixedHeight(42);
    strategyButton->setFixedHeight(42);

    QString buttonStyle =
        "QPushButton {"
            "background-color: #303030;"
            "color: white;"
            "border: 1px solid #555555;"
            "border-radius: 7px;"
            "padding: 8px 15px;"
            "}"
            "QPushButton:hover {"
            "background-color: #3d3d3d;"
            "border: 1px solid #777777;"
            "}"
            "QPushButton:pressed {"
            "background-color: #252525;"
            "}"
            "QPushButton:disabled {"
            "background-color: #202020;"
            "color: #777777;"
        "}";

    parkButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);
    searchButton->setStyleSheet(buttonStyle);
    strategyButton->setStyleSheet(buttonStyle);

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

    QGroupBox* parkingAreaBox = new QGroupBox();
    parkingAreaBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* parkingAreaLayout = new QVBoxLayout(parkingAreaBox);
    parkingAreaLayout->setContentsMargins(10, 10, 10, 10);
    parkingAreaLayout->addWidget(parkingGrid);

    mainLayout->addWidget(parkingAreaTitle);
    mainLayout->addWidget(parkingAreaBox);
    mainLayout->addLayout(buttonLayout);

    parkingAreaBox->setStyleSheet(
        "QGroupBox {"
            "border: 1px solid #444444;"
            "border-radius: 10px;"
            "background-color: #202020;"
        "}"
    );

    for(ParkingSpot* spot : parkingManager->getSpots())
        spot->addObserver(this);

    refreshStatistics();
}

void MainWindow::update(string spotId, bool occupied){
    parkingGrid->refreshSpot(spotId);
    refreshStatistics();
}

MainWindow::~MainWindow(){
    for(Vehicle* vehicle : vehicles)
        delete vehicle;
}