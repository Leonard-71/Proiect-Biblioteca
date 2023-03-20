#ifndef CARTE_H
#define CARTE_H

#include "Functii.h"
#include "Client.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#define x ","
#define y ", "
#define err "\nNu sunt carti in fisier..."
using namespace std;


class Carte
{
    string titlu,data_ap;
    string autor, editura,gen,categorie;
    int nr_buc,disponibil;
    long ISBN;

public:
    Carte();
    ~Carte(){};
    friend ifstream& operator >> (ifstream&, Carte&);
    friend ostream&  operator << (ostream&,  Carte&);
    friend ofstream& operator << (ofstream&, Carte&);
    friend fstream&  operator << (fstream&,  Carte&);
    friend class Client;
    void introducereCarte(string);
    void cautareTitlu(char *,string);
    void cautareAutor(char *,string);
    void afiseazaCarti(string);
    void sorteazaCarti(string);
    void stergereCarte(string,int);
    void modificareCarte(string,long);
    bool cautareId(string,int);

};
#endif // CARTE_H
