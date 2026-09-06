# Parking Lot System

A terminal-based Parking Lot Management System implemented in C++ using object-oriented design and commonly used low-level design patterns.

## Overview

The Parking Lot System manages vehicles, parking spots, parking tickets, parking fees, parking availability, and runtime parking operations.

The system supports configurable parking capacity, automatic parking spot allocation, configurable parking and pricing strategies, vehicle and ticket search, parking statistics, simulated parking fee calculation, and logging.

All data is maintained in memory during program execution. No database or persistent storage is used.

## Features

- Configurable parking capacity
- Multiple parking spot types
- Multiple vehicle types
- Automatic parking spot allocation
- Vehicle parking and exit
- Ticket generation
- Parking fee calculation
- Hourly and flat-rate pricing
- Configurable parking allocation strategies
- Parking availability tracking
- Vehicle search
- Ticket search
- Parking statistics
- Occupancy calculation
- Availability updates through observer notifications
- Runtime logging
- Input validation and error handling
- Dynamic memory management

## Vehicle Types

The system currently supports:

- CAR
- BIKE
- ELECTRIC

## Parking Spot Types

The system currently supports:

- Bike
- Compact
- Large
- Electric

Vehicle-to-spot allocation is handled by the parking strategy.

## Parking Configuration

Parking capacity is configured when the application starts.

Example:

```text
Enter number of Bike spots: 5
Enter number of Compact spots: 10
Enter number of Large spots: 5
Enter number of Electric spots: 3
```

## Design Patterns Used

### 1. Strategy Pattern

Used for parking spot allocation and parking fee calculation. Different strategies can be selected at runtime without changing the parking manager.

### 2. Factory Pattern

Used to create vehicles and parking spots while keeping object creation separate from the main application logic.

### 3. Observer Pattern

Used to notify the display board whenever a parking spot changes between available and occupied.

### 4. Singleton Pattern

Used for the Logger to provide a single logging instance throughout the application.

## Design Principles Used

### 1. Single Responsibility Principle

Classes are designed to focus on specific responsibilities such as vehicle management, parking spot management, pricing, logging, and parking allocation.

### 2. Open/Closed Principle

New parking and pricing strategies can be added without modifying the existing parking manager.

### 3. Dependency Inversion Principle

ParkingManager depends on parking and pricing strategy abstractions rather than concrete strategy implementations.

## Application Workflow

1. Configure parking capacity when the application starts.
2. Create parking spots using the Parking Spot Factory.
3. Select a parking allocation strategy.
4. Park a vehicle and generate a parking ticket.
5. Track parking availability through observer notifications.
6. Exit the vehicle and calculate the parking fee.
7. Search active vehicles or tickets.
8. View parking statistics.
9. Change parking and pricing strategies at runtime.

## Build and Run

Compile the project using g++:

```bash
g++ -std=c++17 -Iinclude src/*.cpp src/parkingStrategy/*.cpp src/pricingStrategy/*.cpp src/observer/*.cpp -o main
```

Run:
```bash
./main.exe
```

## Testing

The application was manually tested for:

- Valid vehicle parking
- Invalid vehicle types
- Duplicate vehicle parking
- Parking lot capacity limits
- Vehicle exit
- Invalid ticket IDs
- Vehicle search
- Ticket search
- Parking strategy changes
- Pricing strategy changes
- Parking availability
- Occupancy statistics