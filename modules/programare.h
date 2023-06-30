#include <string>

#include "../clases/rezervare.h"

using namespace std;
#ifndef VACCIN_PROGRAMARE_H
#define VACCIN_PROGRAMARE_H

void start();
//
int programare();
void findVaccin(string,bool);
//**********to delete*******
void writeInDatabase(rezervare);

//Deleting
rezervare* infoRezervation();
int deleteRezervation(rezervare);
#endif //VACCIN_PROGRAMARE_H