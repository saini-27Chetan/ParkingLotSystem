cmake_minimum_required(VERSION 3.16)

project(ParkingLotSystem VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(ParkingLotSystem
    src/main.cpp

    src/Logger.cpp
    src/ParkingLot.cpp
    src/ParkingManager.cpp
    src/ParkingSpot.cpp
    src/ParkingSpotFactory.cpp
    src/Ticket.cpp
    src/TicketManager.cpp
    src/Vehicle.cpp
    src/VehicleFactory.cpp

    src/parkingStrategy/FirstAvailableSpot.cpp
    src/parkingStrategy/NearestSpot.cpp

    src/pricingStrategy/FlatRatePrice.cpp
    src/pricingStrategy/HourlyPrice.cpp

    src/observer/DisplayBoard.cpp

    ui/src/MainWindow.cpp
    ui/src/ParkingGrid.cpp
    ui/src/dialogs/ParkDialog.cpp
    ui/src/dialogs/ExitDialog.cpp
    ui/src/dialogs/SearchDialog.cpp
    
    ui/include/MainWindow.h
    ui/include/ParkingGrid.h
    ui/include/dialogs/ParkDialog.h
    ui/include/dialogs/ExitDialog.h
    ui/include/dialogs/SearchDialog.h
)

target_include_directories(ParkingLotSystem PRIVATE
    include
    ui/include
)

target_link_libraries(ParkingLotSystem PRIVATE
    Qt6::Widgets
)