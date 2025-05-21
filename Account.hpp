//Account.cpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Header de la clase: contiene los atributos metodos sin las definiciones
Esta clase crea y valida el login o sign up de un usuario. Ademas
administra y contiene las reservaciones de cada cuenta.
*/

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>
#include <vector>
#include "Reservation.hpp"

using namespace std;

class Account {
private:
    string user;
    string password;
    vector<Reservation> bookedFlights;

public:
    //Constructors
    Account();
    Account(string username, string password);

    ~Account();

    //Getters
    string getUser() const;
    string getPassword() const;
    vector<Reservation> get_bookedFlights() const;

    //Setters
    void setUser(string user);
    void setPassword(string password);

    //Others
    void createAccount(string user, string password);
    bool userValidation(string userLogin, string passwordLogin);

    void addReservation(Reservation reservation);
    void removeReservation(string code);
    void displayReservation();
};

#endif