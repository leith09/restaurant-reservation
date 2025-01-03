# Reservation Management System

## Overview
The **Reservation Management System** is a comprehensive C-based program designed to handle restaurant reservations efficiently. It supports adding, viewing, and canceling reservations while adhering to a defined maximum seating capacity. The system ensures data persistence through file storage and employs robust input validation and dynamic memory management.

---

## Features
- **Dynamic Reservation Management**: Add, view, and cancel reservations seamlessly.
- **Capacity Monitoring**: Tracks and enforces the restaurant's seating capacity.
- **Persistent Storage**: Saves reservations to a file and reloads them on program startup.
- **Input Validation**: Ensures correct date and time formats.
- **User-Friendly Interface**: Intuitive menu-driven command-line interface.

---

## Data Structures

### `Reservation`
The `Reservation` structure holds the following information:

```c
typedef struct {
    char *name;    // Customer's name
    char *phone;   // Customer's phone number
    char *date;    // Reservation date in YYYY-MM-DD format
    char *time;    // Reservation time in HH:MM format
    int guests;    // Number of guests
} Reservation;
```

### Constants
- **`MAX_CAPACITY`**: The maximum number of seats available (set to 50).
- **`current_booked_seats`**: Tracks the total number of currently reserved seats.

---

## Functions

### `addReservation`
**Purpose**: Adds a new reservation to the system.

- **Dynamic Memory Allocation**: Allocates memory for new reservations.
- **Input Validation**: Ensures proper date and time formats.
- **Capacity Check**: Prevents overbooking.

### `viewReservations`
**Purpose**: Displays all existing reservations.

- **Formatted Output**: Lists reservations with details (name, phone, date, time, guests).
- **Handles Empty List**: Notifies the user if no reservations are present.

### `cancelReservation`
**Purpose**: Removes an existing reservation.

- **Memory Management**: Frees memory allocated to canceled reservations.
- **Shift Operations**: Maintains a contiguous array by shifting entries.
- **Updates Capacity**: Adjusts the `current_booked_seats` counter.

### `saveToFile`
**Purpose**: Saves all reservations to a file for persistence.

- **File Format**: Stores reservations in a pipe-separated format (`|`).
- **Error Handling**: Notifies users of any file-related issues.

### `loadFromFile`
**Purpose**: Loads reservations from a file on startup.

- **Dynamic Loading**: Allocates memory for each reservation.
- **File Parsing**: Extracts data from a structured file format.

### `validateDate`
**Purpose**: Validates the format of a date string (`YYYY-MM-DD`).

- **Validation Logic**: Ensures the string adheres to the specified format.

### `validateTime`
**Purpose**: Validates the format of a time string (`HH:MM`).

- **Validation Logic**: Ensures the string adheres to the specified format.

---

## Usage Instructions

### Compilation
To compile the program, use the following command:
```bash
gcc -o reservation_system main.c
```

### Execution
To run the program:
```bash
./reservation_system
```

### Menu Options
1. **Add Reservation**: Prompts the user to input details for a new reservation.
2. **View Reservations**: Displays a list of all existing reservations.
3. **Cancel Reservation**: Removes a specified reservation.
4. **Save and Quit**: Saves all data to a file and exits the program.

---

## Input and Output Details

### Input
- **Name**: Up to 100 characters.
- **Phone Number**: Up to 15 characters.
- **Date**: Format `YYYY-MM-DD`.
- **Time**: Format `HH:MM`.
- **Guests**: Positive integer.

### Output
- **Confirmation Messages**: Displays success messages for completed operations.
- **Error Notifications**: Alerts the user to invalid inputs or operational errors.

---

## File Structure

### Source Code
- **`main.c`**: Contains the implementation of the program.

### Data Storage
- **`reservations.txt`**: A file used to store reservations persistently.

---

## Limitations and Future Enhancements

### Current Limitations
- **Date and Time Validation**: Does not verify the logical correctness of dates (e.g., February 30th).
- **Reservation Editing**: Lacks functionality to modify existing reservations.

### Future Enhancements
- **Advanced Validation**: Incorporate logical checks for date and time inputs.
- **Reservation Editing**: Allow updates to existing reservations.
- **Enhanced Interface**: Add a graphical or web-based interface.
- **Data Encryption**: Secure reservation data stored in files.

---

## Conclusion
The Reservation Management System is a robust and extensible tool for managing restaurant reservations. With features like dynamic memory management, input validation, and persistent storage, it ensures efficient and reliable operation. Future enhancements will further elevate its functionality and user experience.

