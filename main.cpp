//main.cpp

/*
Project: ViajandoAndo
A01713458
7/2/2024
*/

/*
Este codigo se encarga de validar la entrada al systema. 
Una vez entrado, el sistema realiza todos los movimientos por si mismo
*/

#include <iostream>
#include <fstream>
#include <iomanip>  //function setw para la tabla
#include <string>
#include <vector>
using namespace std;

#include "Account.hpp"
#include "ReservationSys.hpp"

int main(){
    ReservationSys reservationSys; //accountReservationSystem
    Account account;

    //Data loading process
    reservationSys.loadClients();
    reservationSys.loadFlights();

    //Log In
    cout << "----------------" << endl;
    cout << "Viajando Ando" << endl;
    cout << "----------------" << endl;
    bool enterSystem = false;
    while (enterSystem == false){
        cout << "1) Log In" << endl;
        cout << "2) Sign up" << endl;
        cout << "Select your option by inputing the number: ";
        int login;
        cin >> login;
        if (login == 1){
            cout << "Enter username: " << endl;
            string username;
            cin >> username;
            cout << "Enter password: " << endl;
            string password;
            cin >> password;
            if (account.userValidation(username, password) == true){
                account.setUser(username);
                account.setPassword(password);
                reservationSys.setAccount(account);
                enterSystem = true;
            } else {
                cout << "Incorrect username or password. Please try again" << endl;
            }
    
        } else if (login == 2){
            cout << "Create username: " << endl;
            string username;
            cin >> username;
            cout << "Create password: " << endl;
            string password;
            cin >> password;
            account.createAccount(username, password);
            reservationSys.setAccount(account);
            enterSystem = true;
        } else {
            cout << "Option unavailable " << endl;
        }
    }

    //Entrada al sistema
    cout << "--------------------------" << endl;
    cout << "WELCOME TO VIAJANDO ANDO " << endl;
    cout << "--------------------------" << endl;
    
    reservationSys.optionsMenu();

    return 0;
}