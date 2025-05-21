// reservationSys.cpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Definicion de la clase: contiene las definiciones de los metodos
Esta clase se encarga de realizar el cargado de datos a vectores, al contener vuelos y clientes, 
puede imporimir y flitrar la informacion de los vuelos. Ademas se encarga de realizar, ver o cancelar
las reservaciones y también de operar el menu
*/


#include "ReservationSys.hpp"
#include "Reservation.hpp"
#include "Passenger.hpp"
#include "Flight.hpp"
#include "Account.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

ReservationSys::ReservationSys(){}
ReservationSys::~ReservationSys(){}

//getter and setters
Account ReservationSys::getAccount(){
    return account;
}

void ReservationSys::setAccount(Account account){
    this->account = account;
}

//Cargado de informacion
void ReservationSys::loadClients(){
    ifstream Clientsfile("Clients.txt");
    if (!Clientsfile.is_open()){
        cerr << "Error opening clients file!" << endl;
    }
    std::string line;
    while (getline(Clientsfile, line)){
        stringstream ss(line);
        string fullName, name, lastName;
        int accumulativeKm;
        ss >> name >> lastName >> accumulativeKm;
        fullName = name + " " + lastName;
        Passenger passenger(fullName, accumulativeKm);
        Clients.push_back(passenger);
    }
    Clientsfile.close();
}

// void ReservationSys::printClients() {
//     cout << "printing Clients" << size(Clients) << endl;
//     vector<Passenger>::iterator it = Clients.begin();
//     while (it != Clients.end()){
//         cout << it->getFullName() << " - " << it->getaccumulativeKm() << endl;
//         it++;
//     }
// }

void ReservationSys::loadFlights(){
    ifstream file("Flights.txt");
    if (!file.is_open()) { 
    cerr << "File did not open" << endl; 
    }
    
    //file reading
    string line;
    while (getline(file, line)){
        if (line.empty() || line == "-----") continue;
        stringstream ss(line);
        std::string flightNum, name, origin, destination, boardingTime;
        int day, month, year, duration, totalCapacity, currentCapacity;
        float distance, price;

        // Read flight details from the line
        ss >> flightNum >> name >> origin >> destination >> day >> month >> year >> boardingTime >> duration >> distance >> price >> totalCapacity >> currentCapacity;
        Flight flight(flightNum, name, origin, destination, day, month, year, boardingTime, duration, distance, price, totalCapacity, currentCapacity);

        // Read Manifesto
        getline(file, line);
        for (int i = 0; i < currentCapacity; i++) {
            getline(file, line);
            if (line.empty()) break;
            stringstream ps(line);
            string name, lastname, fullName;
            ps >> name >> lastname;
            fullName = name + " " + lastname;

            // Get accumulative Kilometers
            ifstream fileClients("Clients.txt");
            if (!fileClients.is_open()) { 
                cout << "File did not open" << endl; 
            } 
            string clientLine;
            while (getline(fileClients, clientLine)) {
                stringstream cs(clientLine);
                string clientName, clientLastName, clientFullName;
                int accumulativeKm;
                cs >> clientName >> clientLastName >> accumulativeKm;
                clientFullName = clientName + " " + clientLastName;
                if (clientFullName == fullName) {
                    flight.addPassenger(clientName, accumulativeKm);
                }
            }
            fileClients.close();
        }

        // Read Waitlist
        getline(file, line);
        while (line != "-----") {
            getline(file, line);
            if (line.empty()) break;
            stringstream ps(line);
            string nameW, lastnameW, fullNameW;
            ps >> nameW >> lastnameW;
            fullNameW = nameW + " " + lastnameW;

            // Get accumulative Kilometers
            ifstream fileClients("Clients.txt");
            if (!fileClients.is_open()) { 
                cout << "File did not open" << endl; 
            } 
            string clientLine;
            while (getline(fileClients, clientLine)) {
                stringstream cs(clientLine);
                string clientNameW, clientLastNameW, clientFullNameW;
                int accumulativeKmW;
                cs >> clientNameW >> clientLastNameW >> accumulativeKmW;
                clientFullNameW = clientNameW + " " + clientLastNameW;
                if (clientFullNameW == fullNameW) {
                    flight.addToWaitlist(clientNameW, accumulativeKmW);
                }
            }
            fileClients.close();
        }
        allFlights.push_back(flight);
    }
    cout << "Flights load size: " << size(allFlights) << endl;
    file.close();
}

//Mostrado de vuelos
void ReservationSys::displayFlightHeader(){
    cout << left << setw(12) << "FLT NUM" 
        << setw(18) << "AIRLINE" 
        << setw(15) << "ORIGIN" 
        << setw(10)  << "-->" 
        << setw(15) << "DESTINATION" 
        << setw(12) << "DATE" 
        << setw(14) << "BOARDING" 
        << setw(14) << "DURATION" 
        << setw(14) << "DISTANCE" 
        << setw(10) << "PRICE" 
        << setw(10) << "CAPACITY" << endl;
    cout << string(140, '-') << endl;  // Divider for readability
}

void ReservationSys::displayFlights(){
    cout << "Flights display size: " << size(allFlights) << endl;
    displayFlightHeader();
    vector<Flight>::iterator it = allFlights.begin();
        while (it != allFlights.end()){
            it->printFlight();
            it++;
        }
}

void ReservationSys::displayFilteredFlights(){
    cout << "Select filter method for flight display: " << endl;
    cout << "Enter (1) for those you wish to select " << endl;
    cout << "-) Origin -> Destination";
    bool od;
    cin >> od;
    cout << od << endl;
    cout << "-) Date";
    bool d;
    cin >> d;
    cout << d << endl;
    cout << "-) Airline";
    bool a;
    cin >> a;
    cout << a << endl;

    
    //Origin & Destination, Date, Airline filter
    if (od == true && d == true && a == true){
        string chosenOrigin;
        cout << "Enter Origin: ";
        cin >> chosenOrigin;
        string chosenDestination;
        cout << "Enter Destination: ";
        cin >> chosenDestination;
        string chosenDate;
        cout << "Enter date in DD/MM/YYYY format (don't include unnecesary 0): ";
        cin >> chosenDate;
        string chosenAirline;
        cout << "Enter airline: ";
        cin >> chosenAirline;
        string date;
        displayFlightHeader();
        int results = 0;
        vector<Flight>::iterator it = allFlights.begin();
            while (it != allFlights.end()){
                date = to_string(it->getDay()) + "/" + to_string(it->getMonth()) + "/" + to_string(it->getYear());
                if (it->getOrigin() == chosenOrigin && it->getDestination() == chosenDestination && date == chosenDate && it->getName() == chosenAirline){
                    it->printFlight();
                    results++;
                }
                it++;
            }
        if (results == 0){cout << "No flights found";}

    //Origin & Destination, Date filter
    } else if (od == true && d == true && a == false){
        string chosenOrigin;
        cout << "Enter Origin: ";
        cin >> chosenOrigin;
        string chosenDestination;
        cout << "Enter Destination: ";
        cin >> chosenDestination;
        string chosenDate;
        cout << "Enter date in DD/MM/YYYY format (don't include unnecesary 0): ";
        cin >> chosenDate;
        string date;
        int results = 0;
        displayFlightHeader();
        vector<Flight>::iterator it = allFlights.begin();
            while (it != allFlights.end()){
                date = to_string(it->getDay()) + "/" + to_string(it->getMonth()) + "/" + to_string(it->getYear());
                if (it->getOrigin() == chosenOrigin && it->getDestination() == chosenDestination && date == chosenDate){
                    it->printFlight();
                    results++;
                } 
                it++;
            }
        if (results == 0){cout << "No flights found";}
        
    //Origin & Destination, Airline filter
    } else if (od == true && d == false && a == true){
        string chosenOrigin;
        cout << "Enter Origin: ";
        cin >> chosenOrigin;
        string chosenDestination;
        cout << "Enter Destination: ";
        cin >> chosenDestination;
        string chosenAirline;
        cout << "Enter airline: ";
        cin >> chosenAirline;
        int results = 0;
        displayFlightHeader();
        vector<Flight>::iterator it = allFlights.begin();
            while (it != allFlights.end()){
                if (it->getOrigin() == chosenOrigin && it->getDestination() == chosenDestination && it->getName() == chosenAirline){
                    it->printFlight();
                    results++;
                }
                it++;
            }
        if (results == 0){cout << "No flights found";}

    //Origin & Destination filter
    } else if (od == true && d == false && a == false){
        string chosenOrigin;
        cout << "Enter Origin: ";
        cin >> chosenOrigin;
        string chosenDestination;
        cout << "Enter Destination: ";
        int results = 0;
        displayFlightHeader();
        vector<Flight>::iterator it = allFlights.begin();
            while (it != allFlights.end()){
                if (it->getOrigin() == chosenOrigin && it->getDestination() == chosenDestination){
                    it->printFlight();
                    results++;

                }
                it++;
            }
        if (results == 0){cout << "No flights found";}
    //Date, Airline filter
    } else if (od == false && d == true && a == true){
        string chosenDate;
        cout << "Enter date in DD/MM/YYYY format (don't include unnecesary 0): ";
        cin >> chosenDate;
        string chosenAirline;
        cout << "Enter airline: ";
        cin >> chosenAirline;
        string date;
        int results = 0;
        displayFlightHeader();
        vector<Flight>::iterator it = allFlights.begin();
            while (it != allFlights.end()){
                date = to_string(it->getDay()) + "/" + to_string(it->getMonth()) + "/" + to_string(it->getYear());
                if (date == chosenDate && it->getName() == chosenAirline){
                    it->printFlight();
                    results++;

                }
                it++;
            }
        if (results == 0){cout << "No flights found";}
    //Date filter
    } else if (od == false && d == true && a == false){
        string chosenDate;
        cout << "Enter date in DD/MM/YYYY format (don't include unnecesary 0): ";
        cin >> chosenDate;
        string date;
        int results = 0;
        displayFlightHeader();
        vector<Flight>::iterator it = allFlights.begin();
            while (it != allFlights.end()){
                date = to_string(it->getDay()) + "/" + to_string(it->getMonth()) + "/" + to_string(it->getYear());
                if (date == chosenDate){
                    it->printFlight();
                    results++;

                }
                it++;
            }
        if (results == 0){cout << "No flights found";}
    //Airline filter
    } else if (od == false && d == false && a == true){
        string chosenAirline;
        cout << "Enter airline: ";
        cin >> chosenAirline;
        int results = 0;
        displayFlightHeader();
        vector<Flight>::iterator it = allFlights.begin();
            while (it != allFlights.end()){
                if (it->getName() == chosenAirline){
                    it->printFlight();
                    results++;

                }
                it++;
            }
        if (results == 0){cout << "No flights found";}
    }
}

void ReservationSys::bookFlight(){
    cout << "Enter the flight ID: ";
    string bookingFlightId;
    cin >> bookingFlightId;
    cout << "The selected flight ID corresponds to the following flight information" << endl;
    displayFlightHeader();

    //Using a pointer to select the select flight from the vector and be able to use it's methods
    Flight* selectedFlight = nullptr;
    vector<Flight>::iterator it = allFlights.begin();
    while (it != allFlights.end()){
        if (it->getFlightNumber() == bookingFlightId){
            selectedFlight = &(*it);
            selectedFlight->printFlight();
            break;
        }
        it++;
    }

    if (selectedFlight == nullptr) {
        cout << "Flight not found." << endl;
        return;
    }
    
    cout << "Do you wish to proceed with the reservation? (Enter 1 for Yes)";
    bool reservationProceed;
    cin >> reservationProceed;
    if (reservationProceed != true){
        optionsMenu(); 
        return;
    } 

    //Asks for ticket amount and verifies if they can be booked or if they have to waitlist
    int CurrentCapacity = selectedFlight->getCurrentCapacity();
    int totalCapacity = selectedFlight->getTotalCapacity();
    cout << "How many tickets do you wish to book: ";
    int ticketsBooked;
    cin >> ticketsBooked;
    //Code section for Booking
    if ((ticketsBooked+CurrentCapacity)<=totalCapacity){
        for (int i=0; i<ticketsBooked; i++){
            cout << "Reservation " << i+1 << " out of " << ticketsBooked << endl;
            string passengerName, passengerLastName;

            cout << "Enter only the passenger's first name: ";
            cin >> passengerName;
            cout << "Enter only the passenger's last name: ";
            cin >> passengerLastName;
            string passengerFullName = passengerName + " " + passengerLastName;

            //Verifies passenger isn't already booked
            if (selectedFlight->checkPassengerExistance(passengerFullName) == true){
                cout << "Passenger name already entered, enter another" << endl;
            } else {
            Reservation reservation;

            //Matches acccumulativeKm to check if the passenger is a client and check if they apply for a discount
            int accumulativeKm = 0;
            bool clientFound = false;
            for (auto& client : Clients) {
                if (client.getFullName() == passengerFullName) {
                    accumulativeKm = client.getaccumulativeKm();
                    clientFound = true;
                    if (accumulativeKm>50000){
                        float price = selectedFlight->getPrice();
                        cout << "This passenger has more than 50,000 accumulated km, a 40'%' discount has been aplied, leading the ticket price to be $" << price*0.6 << endl;
                        reservation.setDiscountStatus(true);
                    }
                    client.setaccumulativeKm(accumulativeKm - 50000);
                    break;
                }
            }
            if (!clientFound){
                Clients.push_back(Passenger(passengerFullName, 0));
            }

            //Adds passenger and reservation
            selectedFlight->addPassenger(passengerFullName, accumulativeKm);
            selectedFlight->setCurrentCapacity(CurrentCapacity+1);

            reservation.setCode();
            reservation.setPassenger(passengerFullName);
            reservation.setFlightID(bookingFlightId);
            reservation.setStatus("Booked");
            account.addReservation(reservation);
            }
        }
    //Code section for Waitlist
    } else {
        cout << "Current Capacity for flight " << bookingFlightId << " has been exceeded by your ticket request. Do you wish to be added to a Waitlist? (Input 1 if you do so): ";
        bool waitlist;
        cin >> waitlist;

        for (int i=0; i<ticketsBooked; i++){
            Reservation reservation;
            cout << "Reservation " << i+1 << " out of " << ticketsBooked << endl;
            string passengerName;
            string passengerLastName;

            cout << "Enter only the passenger's first name: ";
            cin >> passengerName;
            cout << "Enter only the passenger's last name: ";
            cin >> passengerLastName;
            string passengerFullName = passengerName + " " + passengerLastName;

            //Verifies passenger isn't already booked
            if (selectedFlight->checkPassengerExistance(passengerFullName) == true){
                cout << "Passenger is already registered in flight, enter another" << endl;
            } else {

            //Matches acccumulativeKm to check if the passenger is a client and create passenger in Waitlist
            
            int accumulativeKm;
            bool clientFound = false;
            for (const auto& client : Clients) {
                if (client.getFullName() == passengerFullName) {
                    accumulativeKm = client.getaccumulativeKm();
                    bool clientFound = true;
                    break;
                }
            }

            if (!clientFound){
                Clients.push_back(Passenger(passengerFullName, 0));
            }

            //Adds waitlisted passenger and reservation
            selectedFlight->addToWaitlist(passengerFullName, accumulativeKm);

            reservation.setCode();
            reservation.setPassenger(passengerFullName);
            reservation.setFlightID(bookingFlightId);
            reservation.setStatus("Waitlisted");
            account.addReservation(reservation);
            }
        }


    }
}

void ReservationSys::cancelBooking(){
    cout << "Which reservation do you wish to cancel: (Enter reservation code)" << endl;
    string resCode;
    cin >> resCode;
    account.removeReservation(resCode);
}

void ReservationSys::seeUserReservations(){
    Account account = getAccount();
    account.displayReservation();
}

void ReservationSys::optionsMenu(){
    Account account = getAccount();
    cout << "Options menu" << endl;
    cout << "1) See flights" << endl;
    cout << "2) Check my reservations" << endl;
    cout << "Enter the option number you wish to select: ";
    int menuOption;
    cin >> menuOption;
    if (menuOption == 1){
        cout << "Choose between options: " << endl;
        cout << "1) Display all available flights" << endl;
        cout << "2) Display filtered list of flights" << endl;
        cout << "Enter the option number you wish to select: ";
        int flightDisplay;
        cin >> flightDisplay;
        if (flightDisplay == 1){
            displayFlights();
        } else if (flightDisplay == 2){
            displayFilteredFlights();
        } else {
            cout << "Chosen option not available, returning to menu" << endl;
            optionsMenu();
        }

        cout << "Do you wish to create a reservation: (Enter 1)" << endl;
        cout << "Note that entering 0 will return you to the menu " << endl;
        bool createReservation;
        cin >> createReservation;
        if (createReservation == true){
            bookFlight();
            optionsMenu();
        } else {
            cout << "Returning to the menu" << endl;
            optionsMenu();
        }
    } else if (menuOption == 2){
        cout << "Your reservations: " << endl;
        seeUserReservations();
        cout << "Choose between options: " << endl;
        cout << "1) Cancel reservation" << endl;
        cout << "2) Return to menu" << endl;
        cout << "Enter the option number you wish to select: ";
        int cancelReservation;
        cin >> cancelReservation;
        if (cancelReservation == 1){
            cancelBooking();
            optionsMenu();
        } else {
            optionsMenu();
        } 
    }
}