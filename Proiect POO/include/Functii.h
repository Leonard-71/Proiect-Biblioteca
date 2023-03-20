#ifndef FUNCTII_H
#define FUNCTII_H
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <conio.h>
#include "Carte.h"
#include "Client.h"
#include <fstream>



using namespace std;

#define err "\nNu sunt carti in fisier..."
using namespace std;

void desen();

int meniu();
int afis_meniu();

void meniu_cautare(string fis);
void afis_cautare();

void meniu_modif(string fis);
void afis_modificare();

void meniu_clienti(string fis,string pfile);
void afis_meniuclienti();

void gotoxy(short,short);

void inf_autor();

int nr_inreg(string);



#endif // FUNCTII_h
