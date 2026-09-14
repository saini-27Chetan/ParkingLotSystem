#include <QFrame>
#include <QSizePolicy>
#include <QVBoxLayout>

#include "ParkingGrid.h"
#include "ParkingManager.h"
#include "ParkingSpot.h"
#include "Ticket.h"
#include "Vehicle.h"
#include "pricingStrategy/PricingStrategy.h"
using namespace std;

ParkingGrid::ParkingGrid(ParkingManager* parkingManager, PricingStrategy* hourlyPricingStrategy, PricingStrategy* flatRatePricingStrategy, QWidget* parent) : QWidget(parent), parkingManager(parkingManager), hourlyPricingStrategy(hourlyPricingStrategy), flatRatePricingStrategy(flatRatePricingStrategy){
    parkingWidget = new QWidget();
    parkingWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    parkingGrid = new QGridLayout(parkingWidget);
    parkingGrid->setContentsMargins(15, 15, 15, 15);
    parkingGrid->setHorizontalSpacing(8);
    parkingGrid->setVerticalSpacing(8);

    int row = 0, column = 0;
    for(ParkingSpot* spot : parkingManager->getSpots()){
        string spotId = spot->getSpotId();
        QString spotType = QString::fromStdString(spot->getSpotType());
        QString buttonText = QString::fromStdString(spotId) + "\n" + spotType;
        QPushButton* spotButton = new QPushButton(buttonText);

        spotButton->setMinimumHeight(110);
        spotButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed );
        parkingGrid->addWidget(spotButton, row, column);
        spotButtons[spotId] = spotButton;

        column++;
        if(column == 4){
            column = 0;
            row++;
        }
    }

    scrollArea = new QScrollArea();
    scrollArea->setWidget(parkingWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(scrollArea);

    for(ParkingSpot* spot : parkingManager->getSpots())
        refreshSpot(spot->getSpotId());
}


void ParkingGrid::refreshSpot(const string& spotId){
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
                text += "Registration Number: ";
                text += QString::fromStdString(spot->getVehicle()->getRegistrationNumber());
                
                Ticket* ticket = parkingManager->findVehicle(spot->getVehicle()->getRegistrationNumber());
                if(ticket != nullptr){
                    text += "\nTicket ID: ";
                    text += QString::fromStdString(ticket->getTicketId());
                    text += "\nPricing: ";
                    if(ticket->getPricingStrategy() == hourlyPricingStrategy)
                        text += "Hourly";
                    else if(ticket->getPricingStrategy() == flatRatePricingStrategy)
                        text += "Flat Rate";
                }
            }
            button->setStyleSheet(
                "QPushButton {"
                    "background-color: #4a2424;"
                    "border: 2px solid #f44336;"
                    "border-radius: 8px;"
                    "color: #ffb3b3;"
                "}"
            );
        }
        else{
            text += "AVAILABLE";
            button->setStyleSheet(
                "QPushButton {"
                    "background-color: #244a2a;"
                    "border: 2px solid #4caf50;"
                    "border-radius: 8px;"
                    "color: #b8f5c0;"
                "}" 
            );
        }

        button->setText(text);
        break;
    }
}