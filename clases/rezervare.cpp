#include "rezervare.h"
rezervare::rezervare() {
    return;
}

string rezervare::getPrenume(){
    return this->Prenume;
}
string rezervare::getNume(){
    return this->Nume;
}
string rezervare::getVaccin(){
    return this->Vaccin;
}
string rezervare::getCentrul(){
    return this->Centrul;
}
int rezervare::getData(){
    return this->dataRezervarii;
}
int rezervare::getLuna(){
    return this->lunaRezervare;
}
/////Setters//////////////
void rezervare::setPrenume(string Name){
    this->Prenume = Prenume;
}
void rezervare::setNume(string Nume){
    this->Nume = Nume;
}
void rezervare::setVaccin(string Vaccin){
    this->Vaccin = Vaccin;
}
void rezervare::setCentrul(string Centrul){
    this->Centrul=Centrul;
}
void rezervare::setData(int data){
    this->dataRezervarii = data;
}
void rezervare::setLuna(int luna){
    this->lunaRezervare = luna;
}
