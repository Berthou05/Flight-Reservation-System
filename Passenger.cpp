//Passenger.cpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Definicion de la clase: contiene las definiciones de los metodos
Esta clase contiene a los pasajeros de los vuelos. Se usaran para reconocer 
los clientes y poder aplicar los descuentos acordes a los 50000 km
*/

#include "Passenger.hpp"

Passenger::Passenger(std::string fullName, int accumulativeKm) : fullName(fullName), accumulativeKm(accumulativeKm){}

Passenger::~Passenger(){}

std::string Passenger::getFullName() const{
    return fullName;
}

int Passenger::getaccumulativeKm() const{
    return accumulativeKm;
}

void Passenger::setName(std::string fullName){
    this->fullName = fullName;
}

void Passenger::setaccumulativeKm(int accumulativeKm){
    this->accumulativeKm = accumulativeKm;
}