// reservation.cpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Definicion de la clase: contiene las definiciones de los metodos
Esta clase crea las reservaciones, creando el codigo y almacenando informacion importante para el cliente
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>  //function setw para la tabla
#include "Reservation.hpp"

using namespace std;

//Constructors
Reservation::Reservation(){}

Reservation::Reservation(string flightID, string passengerName){
    this->flightID = flightID;
    this->passengerName = passengerName;
    this->discount = false;
}

Reservation::~Reservation(){}

//getters
string Reservation::getCode() const{
    return code;
}

string Reservation::getFlightID() const{
    return flightID;
}

string Reservation::getPassenger() const{
    return passengerName;
}

string Reservation::getStatus() const{
    return status;
}

bool Reservation::getDiscountStatus() const{
    return discount;
}

//setters
void Reservation::setFlightID(string flightID){
    this->flightID = flightID;
}

void Reservation::setPassenger(string passengerName){
    this->passengerName = passengerName;
}

void Reservation::setDiscountStatus(bool discount){
    this->discount = discount;
}

void Reservation::setStatus(string status){
    this->status = status;
}

void Reservation::setCode(){
    srand(time(0));
    this->code = generateReservationCode();
}

//Generate code for reservation ID
string Reservation::generateReservationCode() {
    string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string code = "";

    for (int i = 0; i < 6; i++) {
     code += characters[rand() % characters.length()];
    }
    return code;
}


void Reservation::printReservation() const{
    string discountState;
    if (discount==true){
        discountState = "True";
    } else {
        discountState = "False";
    }
    cout << left << setw(25) << code << setw(20) << flightID << setw(20) << passengerName << right << setw(20) << status << setw(25) << discountState << endl;
}

void Reservation::printReservationHeader(){
    cout << left << setw(25) << "Reservation code:" << setw(20) << "Flight ID:" << setw(20) << "Passenger:" << right << setw(20) << "Status:" << setw(25) << "Discount (40%):" << endl;
    cout << string(110, '-') << endl;  // Divider for readability
}
