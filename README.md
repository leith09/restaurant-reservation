README

Reservation Management System

Description

This project is a simple Reservation Management System implemented in C. It allows users to manage restaurant reservations with the following functionalities:

Add a Reservation: Add details of a new reservation, including the name, phone number, date, time, and number of guests.

View Reservations: View all existing reservations with their details.

Cancel a Reservation: Remove a reservation based on its index.

Save and Quit: Save all reservations to a file and exit the program.

Features

Maximum capacity management to prevent overbooking.

Input validation for date and time fields.

Persistent storage using a file (reservations.txt) for saving and loading reservation data.

Memory management to handle dynamic allocation and deallocation of reservation details.

Requirements

A C compiler (e.g., GCC).

A terminal or console to run the program.

How to Compile

To compile the code, use the following command:

gcc -o reservation_system main.c

How to Run

Run the compiled program:

./reservation_system

File Structure

main.c: Main program file containing all logic.

reservations.txt: File used to store reservation details persistently.

Functional Details

1. Add a Reservation

Prompts the user for name, phone number, date, time, and number of guests.

Validates date and time formats.

Ensures the number of guests does not exceed the available capacity.

2. View Reservations

Displays all reservations with details such as name, phone, date, time, and the number of guests.

3. Cancel a Reservation

Cancels a reservation based on its index provided by the user.

Frees memory associated with the canceled reservation.

Adjusts the booked seat count.

4. Save and Quit

Saves all reservations to reservations.txt in a specific format.

Frees all dynamically allocated memory before exiting.

Input Format

Date

Must be in the format: YYYY-MM-DD (e.g., 2025-01-02).

Time

Must be in the format: HH:MM (e.g., 18:30).

Error Handling

Invalid inputs for date and time prompt the user to re-enter.

Errors in memory allocation or file operations are reported.

Prevents adding reservations if the capacity is full.

Limitations

Reservations are limited to the maximum capacity (MAX_CAPACITY = 50).

Reservation details are limited in size: name (100 characters), phone (15 characters), date (10 characters), and time (5 characters).

Basic date and time validation only checks formatting, not actual validity (e.g., 2025-02-30 would be considered valid).

Future Improvements

Advanced date and time validation.

Enhanced user interface.

Support for editing existing reservations.

Example Usage

Adding a Reservation

Input the required details (name, phone, date, time, and number of guests).

Program confirms success and updates the seat count.

Viewing Reservations

Displays all reservations in a formatted list.

Canceling a Reservation

Enter the index of the reservation to cancel.

Program confirms the cancellation and updates the seat count.

Saving and Exiting

Saves reservations to reservations.txt.

Exits the program safely, freeing all allocated memory.


