// reservation.hpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Header de la clase: contiene los atributos metodos sin las definiciones
Esta clase crea las reservaciones, creando el codigo y almacenando informacion importante para el cliente
*/

#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <iostream>
using namespace std;

class Reservation{
private:
string code;
string flightID;
string passengerName;
bool discount;
string status;

public:
//Constructores
Reservation();
Reservation(string flightID, string passengerName);
~Reservation();

//getters
string getCode() const;
string getFlightID() const;
string getPassenger() const;
string getStatus() const;
bool getDiscountStatus() const;

//setters
void setFlightID(string flightID);
void setPassenger(string passengerName);
void setDiscountStatus(bool discount);
void setStatus(string status);
void setCode();

//Others
string generateReservationCode();
void printReservation() const;
void printReservationHeader();
};

#endif