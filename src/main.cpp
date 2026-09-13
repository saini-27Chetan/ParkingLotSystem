#include <QApplication>
#include "MainWindow.h"
#include "ParkingManager.h"
#include "ParkingLot.h"
#include "parkingStrategy/FirstAvailableSpot.h"
#include "parkingStrategy/NearestSpot.h"
#include "pricingStrategy/HourlyPrice.h"
#include "pricingStrategy/FlatRatePrice.h"
#include "observer/DisplayBoard.h"
#include "Logger.h"
using namespace std;

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    Logger& logger = Logger::getInstance();
    logger.log("Parking Lot System started");

    ParkingLot parkingLot;
    int bikeCount = 1;
    int compactCount = 1;
    int largeCount = 1;
    int electricCount = 1;
    vector<ParkingSpot*> spots = parkingLot.createParkingSpots(bikeCount, compactCount, largeCount, electricCount);

    DisplayBoard displayBoard;
    for(ParkingSpot* spot : spots)
        spot->addObserver(&displayBoard);
    
    FirstAvailableSpot parkingStrategy;
    NearestSpot nearestSpot;

    HourlyPrice pricingStrategy;
    FlatRatePrice flatRatePrice;

    ParkingManager parkingManager(
        spots,
        &parkingStrategy,
        &pricingStrategy
    );

    MainWindow window(&parkingManager);
    window.show();

    int result = app.exec();

    for(ParkingSpot* spot : spots)
        delete spot;

    return result;
}