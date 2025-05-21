//Passenger.hpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Header de la clase: contiene los atributos metodos sin las definiciones
Esta clase contiene a los pasajeros de los vuelos. Se usaran para reconocer 
los clientes y poder aplicar los descuentos acordes a los 50000 km
*/

#ifndef PASSENGER_HPP
#define PASSENGER_HPP
#include <iostream>

class Passenger {
private:
    std::string fullName;
    int accumulativeKm;

public:
    //Constructors
    Passenger(std::string fullName, int accumulativeKm);
    virtual ~Passenger();

    //getters
    std::string getFullName() const;
    int getaccumulativeKm() const;
    
    //setters
    void setName(std::string fullName);
    void setaccumulativeKm(int accumulativeKm);
};

#endif