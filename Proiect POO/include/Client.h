#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "Carte.h"

using namespace std;

class Client
{   int nr_crt;
    string nume,adresa;
    string cnp;
    int nr_carti;
    long v[10];
public:
    Client();
    ~Client();
    friend ofstream& operator << (ofstream &, Client&);
    friend ifstream& operator >> (ifstream &, Client&);
    friend fstream& operator << (fstream &,Client&);
    friend ostream& operator << (ostream&, Client&);
    int introducereClient(string,string);
    void inchiriereCarte(string,string);
    void afisareClienti(string);
    void cautareClient(string);
    void restituireCarte(string,string);
    bool cautareCnp(string,string);
    bool cautareNume(string,string);
};
#endif // CLIENT_H
