# Flight Reservation System

Console-based flight reservation system written in C++. The project loads flights, clients, and login credentials from plain text files, then lets a user sign up or log in, browse flights, and create or cancel reservations from a terminal menu.

## Features

- User sign up and log in using `Login.txt`
- Load flight inventory from `Flights.txt`
- Load frequent-client kilometer balances from `Clients.txt`
- Display all flights in tabular format
- Filter flights by origin/destination, date, and airline
- Book one or more seats on a flight
- Add passengers to a waitlist when a flight is full
- Apply a 40% discount for passengers with more than 50,000 accumulated kilometers
- View and cancel reservations created during the current execution

## Tech Stack

- C++
- Standard Library: `iostream`, `fstream`, `vector`, `sstream`, `iomanip`, `string`
- File-based persistence for seed data

## Project Structure

```text
.
|-- main.cpp
|-- Account.hpp / Account.cpp
|-- Passenger.hpp / Passenger.cpp
|-- Flight.hpp / Flight.cpp
|-- Reservation.hpp / Reservation.cpp
|-- ReservationSys.hpp / ReservationSys.cpp
|-- Clients.txt
|-- Flights.txt
|-- Login.txt
```

## How It Works

1. The program starts in `main.cpp`.
2. `ReservationSys` loads clients and flights from the text files.
3. The user chooses to log in or create an account.
4. After authentication, the options menu allows the user to:
   - list all flights,
   - filter flights,
   - create reservations,
   - inspect reservations,
   - cancel reservations.

## Data Files

### `Clients.txt`

Each line stores a passenger name and accumulated kilometers:

```text
FirstName LastName AccumulativeKm
```

Example:

```text
Alice Johnson 48200
```

### `Login.txt`

Each line stores one account:

```text
username password
```

Example:

```text
Alexis 2123
```

### `Flights.txt`

Flights are stored in blocks. Each block contains:

1. A flight header line:

```text
FlightNumber Airline Origin Destination Day Month Year BoardingTime Duration Distance Price TotalCapacity CurrentCapacity
```

2. A `Manifesto:` line
3. `CurrentCapacity` passenger lines
4. A `Waitlist:` line
5. Zero or more waitlisted passengers
6. A `-----` separator

Example:

```text
A123 Delta NewYork LosAngeles 5 2 2025 10:00 360 4000 250.0 4 3
Manifesto:
Alice Johnson
Bob Smith
Charlie Brown
Waitlist:
-----
```

## How to Compile

### Requirements

- A C++ compiler such as `g++`
- A terminal opened in the project root

### Source Files

Compile these files together:

```text
main.cpp Account.cpp Passenger.cpp Flight.cpp Reservation.cpp ReservationSys.cpp
```

### Example Command

From PowerShell:

```powershell
g++ main.cpp Account.cpp Passenger.cpp Flight.cpp Reservation.cpp ReservationSys.cpp -o FlightReservationSystem.exe
```

From a Unix-like shell:

```bash
g++ main.cpp Account.cpp Passenger.cpp Flight.cpp Reservation.cpp ReservationSys.cpp -o FlightReservationSystem
```

### Important Note

The current repository state does not compile cleanly with `g++` in this environment without code fixes. If you want to run the project immediately, use one of the prebuilt executables already included in the repository.

## Run

The repository already includes prebuilt Windows executables:

```powershell
.\main.exe
```

or

```powershell
.\ReservationSys.exe
```

## Main Classes

- `Account`: handles login, signup, and the reservations attached to the current session.
- `Passenger`: stores passenger name and accumulated kilometers.
- `Flight`: stores flight details plus booked and waitlisted passengers.
- `Reservation`: stores reservation code, flight ID, passenger name, status, and discount flag.
- `ReservationSys`: coordinates file loading, menus, flight display/filtering, and booking flow.

## Notes and Current Limitations

- Reservation data is kept in memory for the active run; it is not written back to a file.
- Changes made while booking or canceling do not persist after the program exits.
- Login validation checks username and password pairs from `Login.txt`.
- Input parsing assumes names are exactly two words: first name and last name.
- The interface is fully terminal-based and expects valid numeric input in menus.
- The current source tree includes prebuilt executables, but a fresh `g++` build is not verified without additional code cleanup.

## Sample Use Cases

- Browse all available flights before booking.
- Search for flights by route, date, or airline.
- Book several passengers in one operation.
- Add passengers to a waitlist when remaining capacity is insufficient.
- Apply frequent-client discounts based on accumulated kilometers.

## Authors

Project header comments identify the project as `ViajandoAndo` and include author/student id metadata in the source files.
