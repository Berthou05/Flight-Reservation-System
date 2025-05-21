//Account.cpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Definicion de la clase: contiene las definiciones de los metodos
Esta clase crea y valida el login o sign up de un usuario. Ademas
administra y contiene las reservaciones de cada cuenta.
*/

#include "Account.hpp"
#include "Flight.hpp"
#include "Reservation.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

Account::Account(){}
Account::Account(string username, string password){}

Account::~Account(){}

string Account::getUser() const{
    return user;
}  

string Account::getPassword() const{
    return password;
}

vector<Reservation> Account::get_bookedFlights() const{
    return bookedFlights;
}

void Account::setUser(string user){
    this->user = user;
}

void Account::setPassword(string password){
    this->password = password;
}

void Account::createAccount(string user, string password){
    if (userValidation(user, password)==false){
    ofstream Accounts("Login.txt", ios::app); //Open in append mode
    if (!Accounts.is_open()) {
        cout << "File did not open" << endl;
    }
    Accounts << user << " " << password << endl;
    Accounts.close();
    this->user = user;
    this->password = password;
    cout << "Account created" << endl;
    } else {
        cout << "User already exists" << endl;
    }
}

bool Account::userValidation(string userLogin, string passwordLogin){
    ifstream Accounts("Login.txt");
    if (!Accounts.is_open()) {
        cout << "File did not open" << endl;
    }
    string user, password;
    while (Accounts >> user >> password){
        if (user == userLogin && password == passwordLogin){
            return true;
        }
    }
    Accounts.close();
    return false;
}

void Account::displayReservation(){
    cout << "You have: " << size(bookedFlights) << " reservations" << endl;
    vector<Reservation>::iterator it = bookedFlights.begin();
        it->printReservationHeader();
        while (it != bookedFlights.end()){
            it->printReservation();
            it++;
        }
}

void Account::addReservation(Reservation reservation){
    bookedFlights.push_back(reservation);
    cout << "Reservation created under the following code: " << reservation.getCode() << endl;
}

void Account::removeReservation(string code){
    vector<Reservation>::iterator it = bookedFlights.begin();
    while (it != bookedFlights.end()){
        if (it->getCode() == code){
            it = bookedFlights.erase(it);
        } else {
            ++it;
        }
    }
}