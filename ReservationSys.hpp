// reservationSys.hpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Header de la clase: contiene los atributos metodos sin las definiciones
Esta clase se encarga de realizar el cargado de datos a vectores, al contener vuelos y clientes, 
puede imporimir y flitrar la informacion de los vuelos. Ademas se encarga de realizar, ver o cancelar
las reservaciones y también de operar el menu
*/

#ifndef RESERVATIONSYS_HPP
#define RESERVATIONSYS_HPP

#include <iostream>
#include <fstream>
#include <vector>

#include "Passenger.hpp"
#include "Flight.hpp"
#include "Account.hpp"
#include "Reservation.hpp"

class ReservationSys {
private:
    Account account;
    vector<Flight> allFlights;
    vector<Passenger> Clients;

public:
    ReservationSys();
    ~ReservationSys();

    //getter
    Account getAccount();

    //setter
    void setAccount(Account account);

    //Data manipulation (load and save from .txt files)
    void loadFlights();
    void loadClients();

    //Show flights
    void displayFlightHeader();
    void displayFlights();
    void displayFilteredFlights();

    //reservation manipulation
    void bookFlight();
    void cancelBooking();
    void seeUserReservations();

    // void printClients(); //usado para debugging
    
    //Menu
    void optionsMenu();
};
#endif
