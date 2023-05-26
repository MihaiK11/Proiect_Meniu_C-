#include <string>

using namespace std;
#ifndef VACCINC___REZERVARE_H
#define VACCINC___REZERVARE_H
class rezervare{
    string Prenume;
    string Nume;
    string Vaccin;
    string Centrul;
    int dataRezervarii;
    int lunaRezervare;
public:
    rezervare();
    /////Getters//////////////
    string getPrenume();
    string getNume();
    string getVaccin();
   string getCentrul();
    int getData();
    int getLuna();
    /////Setters//////////////
   void setPrenume(string Name);
    void setNume(string Nume);
    void setVaccin(string Vaccin);
    void setCentrul(string Centrul);
    void setData(int data);
    void setLuna(int luna);
};
#endif //VACCINC___REZERVARE_H
