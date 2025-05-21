//Flight.cpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Header de la clase: contiene los atributos metodos sin las definiciones
Esta clase contiene a los vuelos. Es decir, almacena la informacion
de cada vuelo y ademas se encarga de modificar la informacion de
los vuelos, como modificar pasajeros, quitarlos o agregarlos a la 
waitlist
*/

#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <iostream>
#include <vector>
#include "Passenger.hpp"
using namespace std;

class Flight {
private:
    string flightNum;
    string name;
    string Origin;
    string Destination;
    int day;
    int month;
    int year;
    string boardingTime;
    int duration;
    float distance;
    float price;
    int totalCapacity;
    int currentCapacity;
    vector<Passenger> bookedPassengers;
    vector<Passenger> waitlistedPassengers;
public:
    //Constructors
    Flight(string flightNum, string name, string Origin, string Destination, int day, int month, int year, string boardingTime, int duration, float distance, float price, int totalCapacity, int currentCapacity);
    ~Flight();

    //Getters
    string getFlightNumber() const;
    string getName() const;
    string getOrigin() const;
    string getDestination() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    string getBoardingTime() const;
    int getDuration() const;
    float getDistance() const;
    float getPrice() const;
    int getTotalCapacity() const;
    int getCurrentCapacity() const;
    vector<Passenger> getBookedPassengers() const;
    vector<Passenger> getWaitlistedPassengers() const;

    //Setters
    void setFlightNumber(string flightNumber);
    void setName(string name);
    void setOrigin(string Origin);
    void setDestination(string Destination);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    void setBoardingTime(string boardingTime);
    void setDuration(int duration);
    void setDistance(float distance);
    void setPrice(float price);
    void setTotalCapacity(int totalCapacity);
    void setCurrentCapacity(int currentCapacity);

    //others
    void printFlight();
    void addPassenger(string fullName, int accumulativeKm);
    void removePassenger(string fullName);
    void addToWaitlist(string fullName, int accumulativeKm);
    bool checkPassengerExistance(string passengerName);
};

#endif