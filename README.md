# Parking Lot System

A C++ Parking Lot Management System designed using object-oriented programming, SOLID principles, and commonly used low-level design patterns. Version 2 extends the original terminal-based system with a Qt-based graphical user interface while retaining the core parking lot backend.

## Overview

The Parking Lot System manages vehicles, parking spots, parking tickets, parking fees, parking availability, parking allocation strategies, and runtime parking operations.

Version 2 provides a Qt GUI for interacting with the parking lot. The GUI displays parking spots visually, shows parking statistics, supports vehicle parking and exit operations, provides vehicle and ticket search, allows the parking allocation strategy to be changed at runtime, and displays the pricing strategy associated with each active parking ticket.

All application data is maintained in memory during program execution. No database or persistent storage is used.

## Features

- Qt-based graphical user interface
- Configurable parking capacity
- Multiple parking spot types
- Multiple vehicle types
- Automatic parking spot allocation
- Vehicle parking and exit
- Ticket generation
- Parking fee calculation
- Hourly pricing
- Flat-rate pricing
- Per-ticket pricing strategy selection
- First Available parking strategy
- Nearest Available parking strategy
- Runtime parking strategy changes
- Parking availability tracking
- Vehicle search by registration number
- Vehicle search by ticket ID
- Parking statistics
- Total, occupied, and available spot counts
- Visual parking grid
- Occupied and available spot indication
- Ticket ID and pricing information displayed for occupied spots
- Observer-based parking availability updates
- Registration number format validation
- Input validation and error handling
- Runtime logging
- Factory-based object creation
- Dynamic memory management

## Vehicle Types

The system currently supports:

- `CAR`
- `BIKE`
- `ELECTRIC`

## Parking Spot Types

The system currently supports:

- `Bike`
- `Compact`
- `Large`
- `Electric`

Vehicle-to-spot compatibility is handled by the parking allocation strategy and the parking spot type.

The current compatibility is:

| Vehicle Type | Compatible Spot Types |
|---|---|
| BIKE | Bike |
| CAR | Compact, Large |
| ELECTRIC | Electric |

## Parking Strategies

The system supports two parking allocation strategies.

### First Available Spot

`FirstAvailableSpot` searches the parking spots in their configured order and selects the first compatible available spot.

### Nearest Available Spot

`NearestSpot` selects the compatible available spot closest to the parking entrance using the spot position and Euclidean distance.

The parking entrance is represented at:

```text
(0.0, -8.0)
```

Parking spots are assigned positions when the parking lot is created.

The current parking layout uses:

- 4 spots per row
- 2 ft spacing between spots in the same row
- 8 ft spacing between rows

The active parking allocation strategy can be changed at runtime through the GUI.

Changing the parking strategy affects future parking operations. It does not move vehicles that are already parked.

## Pricing Strategies

The system currently supports two pricing strategies.

### Hourly Pricing

`HourlyPrice` charges:

- ₹50 per hour
- Partial hours are rounded up
- Minimum charge is ₹50

For example, parking for 1 hour and 20 minutes is charged as 2 hours.

### Flat Rate Pricing

`FlatRatePrice` charges:

```text
₹100
```

for the parking session.

### Per-Ticket Pricing

The pricing strategy is selected when a vehicle is parked and is stored with its parking ticket.

For example:

```text
Vehicle A → Ticket T1 → Hourly Pricing
Vehicle B → Ticket T2 → Flat Rate Pricing
```

Therefore, changing the pricing selection for a new parking operation does not change the pricing strategy of vehicles that are already parked.

## Registration Number Validation

The GUI validates vehicle registration numbers using the following format:

```text
XX00XX0000
```

Where:

- `X` represents an English alphabet character (`A-Z`)
- `0` represents a digit (`0-9`)

Examples of valid registration numbers:

```text
UP32AB1234
HR26AX1234
DL01CA4567
```

The registration input field:

- Accepts alphanumeric characters
- Allows a maximum of 10 characters
- Normalizes the registration number to uppercase
- Performs exact format validation before parking

## GUI

Version 2 introduces a Qt-based graphical interface.

The main window provides:

- Application title
- Total parking spot count
- Occupied spot count
- Available spot count
- Current parking allocation strategy
- Visual parking area
- Park Vehicle action
- Exit Vehicle action
- Search action
- Change Parking Strategy action

### Parking Grid

Each parking spot is represented as a button in the parking grid.

Available spots are visually displayed as available, while occupied spots display information including:

```text
Parking Spot
Spot Type
OCCUPIED
Registration Number
Ticket ID
Pricing
```

The parking grid is placed inside a scrollable area so that larger parking configurations can be displayed.

### Park Vehicle

The `Park Vehicle` dialog collects:

- Registration number
- Vehicle type
- Pricing type

The dialog validates the registration number before allowing the operation to proceed.

### Exit Vehicle

The `Exit Vehicle` dialog accepts a ticket ID.

Before completing an exit operation, the user is asked to confirm the exit.

The system then:

1. Finds the active ticket
2. Calculates the parking fee using the pricing strategy stored in the ticket
3. Removes the vehicle from the parking spot
4. Removes the active ticket
5. Updates the GUI

### Search

The GUI supports two search operations:

- Search Vehicle by Registration Number
- Search Vehicle by Ticket ID

Search results are based on currently active parking tickets.

### Change Parking Strategy

The GUI provides two choices:

```text
First Available Spot
Nearest Available Spot
```

The currently selected strategy is displayed in the parking area.

Changing this strategy affects future vehicle parking operations.

## Observer Updates

The Observer pattern is used to notify interested components when a parking spot changes between occupied and available states.

The main relationship is:

```text
ParkingSpot
     |
     | notify
     v
ParkingObserver
     |
     +---- MainWindow
     |
     +---- DisplayBoard
```

`MainWindow` receives the update and refreshes:

- The affected parking spot in the GUI
- Parking statistics

`DisplayBoard` receives parking spot updates and displays the corresponding availability information.

## Design Patterns Used

### 1. Strategy Pattern

The Strategy pattern is used for both parking spot allocation and parking fee calculation.

Parking allocation:

```text
ParkingSpotStrategy
├── FirstAvailableSpot
└── NearestSpot
```

Pricing:

```text
PricingStrategy
├── HourlyPrice
└── FlatRatePrice
```

This allows parking and pricing behavior to vary without modifying `ParkingManager`.

### 2. Factory Pattern

Factory classes are used to separate object creation from the rest of the application logic.

```text
VehicleFactory
ParkingSpotFactory
```

`VehicleFactory` creates vehicles, while `ParkingSpotFactory` creates parking spots.

### 3. Observer Pattern

The Observer pattern is used for parking spot state updates.

```text
ParkingObserver
├── MainWindow
└── DisplayBoard
```

Parking spots notify observers when their occupancy state changes.

### 4. Singleton Pattern

The `Logger` class uses the Singleton pattern to provide a single logging instance throughout the application.

## Design Principles Used

### Single Responsibility Principle

Classes are designed to focus on specific responsibilities.

Examples:

- `Vehicle` manages vehicle information.
- `ParkingSpot` manages parking spot state.
- `Ticket` stores parking session information.
- `TicketManager` manages active tickets and their lifecycle.
- `ParkingManager` coordinates parking and exit operations.
- `PricingStrategy` implementations calculate parking fees.
- `ParkingSpotStrategy` implementations determine parking spot allocation.
- `ParkingGrid` manages the visual parking grid.
- Dialog classes handle specific GUI input operations.
- `Logger` handles application logging.

### Open/Closed Principle

New parking allocation and pricing strategies can be added by implementing the corresponding strategy interfaces without modifying the existing strategy-independent logic in `ParkingManager`.

### Dependency Inversion Principle

`ParkingManager` works with the `ParkingSpotStrategy` and `PricingStrategy` abstractions instead of depending directly on specific strategy implementations.

## Main Components

### Backend

- `ParkingManager` — Coordinates vehicle parking, spot allocation, vehicle exit, ticket handling, and parking availability.
- `TicketManager` — Creates, stores, searches, and removes active parking tickets.
- `Ticket` — Represents a parking session and stores the vehicle, parking spot, entry time, and pricing strategy.
- `ParkingSpot` — Represents an individual parking spot and manages its occupancy state.
- `Vehicle` — Stores vehicle information.
- `ParkingSpotStrategy` — Defines the parking spot allocation behavior.
- `FirstAvailableSpot` — Allocates the first compatible available spot.
- `NearestSpot` — Allocates the nearest compatible available spot.
- `PricingStrategy` — Defines parking fee calculation behavior.
- `HourlyPrice` — Implements hourly pricing.
- `FlatRatePrice` — Implements flat-rate pricing.
- `ParkingSpotFactory` — Creates parking spot objects.
- `VehicleFactory` — Creates vehicle objects.
- `DisplayBoard` — Receives parking spot updates through the Observer pattern.
- `Logger` — Provides centralized logging through the Singleton pattern.

### Qt UI

- `MainWindow` — Main application window and UI coordinator.
- `ParkingGrid` — Displays and refreshes the visual parking spot grid.
- `ParkDialog` — Collects vehicle and pricing information for parking.
- `ExitDialog` — Collects the ticket ID for vehicle exit.
- `SearchDialog` — Handles search input.

## Project Structure

```text
ParkingLotSystem_LLD/
├── include/
│   ├── observer/
│   ├── parkingStrategy/
│   ├── pricingStrategy/
│   ├── Logger.h
│   ├── ParkingLot.h
│   ├── ParkingManager.h
│   ├── ParkingSpot.h
│   ├── ParkingSpotFactory.h
│   ├── Ticket.h
│   ├── TicketManager.h
│   ├── Vehicle.h
│   └── VehicleFactory.h
│
├── src/
│   ├── observer/
│   ├── parkingStrategy/
│   ├── pricingStrategy/
│   ├── Logger.cpp
│   ├── main.cpp
│   ├── ParkingLot.cpp
│   ├── ParkingManager.cpp
│   ├── ParkingSpot.cpp
│   ├── ParkingSpotFactory.cpp
│   ├── Ticket.cpp
│   ├── TicketManager.cpp
│   ├── Vehicle.cpp
│   └── VehicleFactory.cpp
│
├── ui/
│   ├── include/
│   │   ├── dialogs/
│   │   │   ├── ParkDialog.h
│   │   │   ├── ExitDialog.h
│   │   │   └── SearchDialog.h
│   │   ├── mainWindow.h
│   │   └── ParkingGrid.h
│   │
│   └── src/
│       ├── dialogs/
│       │   ├── ParkDialog.cpp
│       │   ├── ExitDialog.cpp
│       │   └── SearchDialog.cpp
│       ├── mainWindow.cpp
│       └── ParkingGrid.cpp
│
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Application Workflow

The main parking workflow is:

```text
User
  |
  v
Park Vehicle Dialog
  |
  | Registration Number
  | Vehicle Type
  | Pricing Type
  v
MainWindow
  |
  v
ParkingManager
  |
  +---- ParkingSpotStrategy
  |          |
  |          v
  |     Find compatible spot
  |
  +---- ParkingSpot
  |          |
  |          v
  |     Park vehicle
  |
  +---- TicketManager
             |
             v
        Create Ticket
             |
             v
        Update GUI
```

The exit workflow is:

```text
User
  |
  v
Exit Vehicle Dialog
  |
  v
ParkingManager
  |
  v
Find Ticket
  |
  v
Get Pricing Strategy
  |
  v
Calculate Fee
  |
  v
Remove Vehicle from Spot
  |
  v
Remove Ticket
  |
  v
Update GUI
```

## Build and Run

Version 2 uses Qt 6 and CMake.

### Requirements

- C++17 compatible compiler
- Qt 6
- CMake
- Qt Widgets module
- MinGW 64-bit or another supported Qt compiler kit

The project was developed and tested using:

```text
Qt 6.11.2
Desktop Qt 6.11.2 MinGW 64-bit
C++17
```

### Build Using CMake

Create a build directory:

```bash
mkdir build
cd build
```

Configure the project:

```bash
cmake ..
```

Build:

```bash
cmake --build .
```

Run the generated application from the build output directory.

The project can also be opened and built directly using Qt Creator with the configured Qt 6 kit.

## Testing

The application has been manually tested for the following scenarios:

- Valid vehicle parking
- Different vehicle types
- Vehicle-to-spot compatibility
- Duplicate vehicle parking
- Invalid registration numbers
- Registration number length validation
- Invalid registration characters
- Parking when no compatible spot is available
- Hourly pricing
- Flat-rate pricing
- Ticket generation
- Vehicle exit using ticket ID
- Invalid ticket ID
- Attempting to exit an already exited vehicle
- Vehicle search
- Ticket search
- Search after vehicle exit
- Parking strategy changes
- Parking strategy changes while vehicles are already parked
- Pricing strategy selection for individual parking sessions
- Parking availability updates
- Occupied and available spot display
- Parking statistics
- Scrollable parking grid
- GUI error and warning states

## Version History

### Version 1.0

The initial version provided a terminal-based C++ Parking Lot Management System with:

- Object-oriented design
- Vehicle and parking spot management
- Ticket management
- Parking strategies
- Pricing strategies
- Factory pattern
- Strategy pattern
- Observer pattern
- Singleton Logger

### Version 2.0

Version 2 extends the system with a Qt-based graphical user interface and improves the separation between the UI and parking management backend.

Major additions include:

- Qt GUI
- Visual parking grid
- Park, Exit, and Search dialogs
- Parking statistics
- Parking strategy indicator
- Runtime parking strategy selection
- Per-ticket pricing strategy
- Registration number validation
- Improved error handling
- Scrollable parking area
- UI/backend separation

## Future Improvements

Possible future extensions include:

- Persistent database storage
- Multiple parking floors
- Different parking entrances
- Reservation support
- Payment integration
- Authentication and user management
- Automated GUI testing
- Additional parking and pricing strategies