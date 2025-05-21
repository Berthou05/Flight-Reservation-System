//Flight.cpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Definicion de la clase: contiene las definiciones de los metodos
Esta clase contiene a los vuelos. Es decir, almacena la informacion
de cada vuelo y ademas se encarga de modificar la informacion de
los vuelos, como modificar pasajeros, quitarlos o agregarlos a la 
waitlist
*/

#include "Flight.hpp"
#include "Passenger.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  //function setw para la tabla
using namespace std;

//Constructors
Flight::Flight(string flightNum, string name, string Origin, string Destination, int day, int month, int year, string boardingTime, int duration, float distance, float price, int totalCapacity, int currentCapacity){
    this->flightNum=flightNum;
    this->name=name;
    this->Origin=Origin;
    this->Destination=Destination;
    this->day=day;
    this->month=month;
    this->year=year;
    this->boardingTime=boardingTime;
    this->duration=duration;
    this->distance=distance;
    this->price=price;
    this->totalCapacity=totalCapacity;
    this->currentCapacity=currentCapacity;
}

Flight::~Flight(){}

//Getters
string Flight::getFlightNumber() const{
    return flightNum;
}

string Flight::getName() const{
    return name;
}

string Flight::getOrigin() const{
    return Origin;
}

string Flight::getDestination() const{
    return Destination;
}

int Flight::getDay() const{
    return day;
}

int Flight::getMonth() const{
    return month;
}

int Flight::getYear() const{
    return year;
}

string Flight::getBoardingTime() const{
    return boardingTime;
}

int Flight::getDuration() const{
    return duration;
}

float Flight::getDistance() const{
    return distance;
}

float Flight::getPrice() const{
    return price;
}

int Flight::getTotalCapacity() const{
    return totalCapacity;
}

int Flight::getCurrentCapacity() const{
    return currentCapacity;
}

//Setters
void Flight::setFlightNumber(string flightNumber){
    this->flightNum = flightNumber;
}

void Flight::setName(string name){
    this->name = name;
}

void Flight::setOrigin(string Origin){
    this->Origin = Origin;
}

void Flight::setDestination(string Destination){
    this->Destination = Destination;
}

void Flight::setDay(int day){
    this->day = day;
}

void Flight::setMonth(int month){
    this->month = month;
}

void Flight::setYear(int year){
    this->year = year;
}

void Flight::setBoardingTime(string boardingTime){
    this->boardingTime = boardingTime;
}

void Flight::setDuration(int duration){
    this->duration = duration;
}

void Flight::setDistance(float distance){
    this->distance = distance;
}

void Flight::setPrice(float price){
    this->price = price;   
}

void Flight::setTotalCapacity(int totalCapacity){
    this->totalCapacity = totalCapacity;
}

void Flight::setCurrentCapacity(int currentCapacity){
    this->currentCapacity = currentCapacity;
}

//Others
void Flight::printFlight(){
    string date;
    date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    cout << left << setw(12) << flightNum
        << setw(18) << name
        << setw(15) << Origin
        << setw(10)  << "-->"
        << setw(15) << Destination
        << setw(12) << date 
        << setw(14) << boardingTime
        << setw(4) << duration << setw(10)  << "min"
        << setw(6) << distance << setw(8)  << "km"
        <<"$" << setw(9) <<  price
        << currentCapacity <<"/"<< totalCapacity << " PAX" << endl;
}

void Flight::addPassenger(string fullName, int accumulativeKm){
    bookedPassengers.push_back(Passenger(fullName, accumulativeKm));
}

void Flight::addToWaitlist(string fullName, int accumulativeKm){
    waitlistedPassengers.push_back(Passenger(fullName, accumulativeKm));
}

bool Flight::checkPassengerExistance(string passengerName){
    for (const auto& passengers : bookedPassengers) {
        if (passengers.getFullName() == passengerName){
            return true;
            break;
        }
    } return false;
}