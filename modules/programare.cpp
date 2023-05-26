#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <cstring>

#include "programare.h"
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void start(){
    SetConsoleTextAttribute(hConsole, 9);
    std::cout << "Alegeti optiune:" << std::endl;
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << "1.Afisarea centrelor de vaccinare:" << std::endl;
    std::cout << "2.Cautarea vaccin" << std::endl;
    std::cout << "3.Programare vaccinare" << std::endl;
    std::cout << "4.Stergere rezervare" << std::endl;
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "*.Exit" << std::endl;
    SetConsoleTextAttribute(hConsole, 15);
    return;
}
int dayInMonth(int month){
    int rezult = 0;
    if (month == 1){
        rezult = 28;
    }else if (month < 7 && month%2 == 0){
        rezult = 31;
    }else if(month > 7 && month%2==1){
        rezult = 31;
    }else{
        rezult = 30;
    }
    return rezult;
}
string concatenateString(rezervare persoana){
    string rez;
    string data;
    string luna;
    //Concatenate date
    data = to_string(persoana.getData());
    luna = to_string(persoana.getLuna());
    //Concatenate All strings
    rez.append(persoana.getPrenume());
    rez.append(",");
    rez.append(persoana.getNume());
    rez.append(",");
    rez.append(data);
    rez.append(".");
    rez.append(luna);
    rez.append(",");
    rez.append(persoana.getVaccin());
    rez.append(",");

    return rez;
}
string getfield(string lineMain, int num){
    string line = lineMain;
    string tok;
    for (tok = line.substr(0, line.find(","));
         tok.length() > 0;
         tok = line.substr(0, line.find(",")))
    {
        if (!--num)
            return tok;
        line = line.substr(line.find(",") + 1);
    }
    return "&";
}

bool file_exists(const char *filename)
{
    ifstream fp(filename);
    bool is_exist = false;
    if (fp.good())
    {
        is_exist = true;
        fp.close(); // close the file
    }
    return is_exist;
}

void writeInDatabase(struct rezervare persoana){
    std::ofstream fpt;
    std::string row;
    if(file_exists("../rezervare.csv")){
        fpt.open("../rezervare.csv", std::ios::app);
        fpt << "\n" << persoana.getPrenume() << "," << persoana.getNume() << "," << persoana.getData() << "." << persoana.getLuna() << "," << persoana.getVaccin() << ",";
        fpt.close();
    } else{
        fpt.open("../rezervare.csv", std::ios::app);
        fpt << "Prenume,Nume,Data,Vaccin,";
        fpt << "\n" << persoana.getPrenume() << "," << persoana.getNume() << "," << persoana.getData() << "." << persoana.getLuna() << "," << persoana.getVaccin() << ",";
        fpt.close();
    }
    return;
}

int checkIfVaccinInData(std::string vaccin){
    int hasVaccin =0;
    std::ifstream fp;
    std::string row;

    fp.open("../data.csv", std::ios::in);
    std::getline(fp, row);
    while (std::getline(fp, row))
    {
        std::string tmp = row;
        if (getfield(tmp, 3) == vaccin) {//If vaccin exist in database on field 3
            hasVaccin = 1;
            break;
        }
    }
    fp.close();
    return hasVaccin;
}

string chooseCenter(string vaccin){
    std::fstream fp;
    string row,center;
    string avaliableCenter[9];
    int i=0;

    fp.open("../data.csv", std::ios::in);
    getline(fp, row, ' ');

    if(!fp.eof()){std::cout << "Alegeti centrul:\n\n";}
    while (!fp.eof()) {
        getline(fp, row, ' ');
        if (row.find(vaccin) != NULL && i<10) {
            int len = row.length();
            int lenVaccin = vaccin.length();
            row[len - lenVaccin - 1] = '\0';
            avaliableCenter[i] = row;
            std::cout << i + 1 << "." << row << std::endl;
            i++;
        }
    }
    std::cout << i + 1 << ".Inapoi\n";

    char answer[20];
    std::cin >> answer;
    std::cout << "\x1b[1F";
    std::cout << "\x1b[2K";
    if (atoi(answer) == 0 || atoi(answer)>i+1){
        while(atoi(answer) == 0 || atoi(answer)>i){
            std::cin >> answer;
            std::cout << "\x1b[1F";
            std::cout << "\x1b[2K";
        };
    }else if (atoi(answer) == i+1) {
        return "Back";
    }
    fp.close();
    return avaliableCenter[atoi(answer)-1];
}
int programare(){
    system("cls");
    string tmp;
    rezervare persoana = rezervare();
    cout << "Introduceti nume: ";
    cin >> tmp;
    persoana.setNume(tmp);

    cout << "Introduceti prenumele: ";
    cin >> tmp;
    persoana.setPrenume(tmp);

    cout << "Introduceti vaccinul: ";
    cin >> tmp;
    persoana.setVaccin(tmp);


    if (checkIfVaccinInData(persoana.getVaccin())){
        system("cls");
        persoana.setCentrul(chooseCenter(persoana.getVaccin()) );
        system("cls");
        if (persoana.getCentrul()!="Back"){//If center exist
            time_t t = time(NULL);//Get today time
            struct tm date = *localtime(&t);
            char readData[20];
            int dataNow = date.tm_mday+1;
            int monthNow = date.tm_mon+1;
            int monthNext = date.tm_mon+2;
            if (monthNext > 12)monthNext-=12;
            int dataNext = dataNow-1;
            std::cout << "Alegeti doar data " << dataNow << "." << monthNow << "-" << dataNext << "." << monthNext << std::endl;
            std::cin >> readData;// Read date of rezervation
            std::cout << "\x1b[1F";
            std::cout << "\x1b[2K";

            while (atoi(readData) < 1 || atoi(readData) > dayInMonth(date.tm_mon)){
                system("cls");
                std::cout << "Incorect date\n";

                std::cin >> readData;
                std::cout << "\x1b[1F";
                std::cout << "\x1b[2K";
            }
            persoana.setData(atoi(readData));
            if (persoana.getData() > date.tm_mday){
                persoana.setLuna(date.tm_mon + 1);
            }else{
                persoana.setLuna( date.tm_mon + 2);
            }
            if(persoana.getLuna() > 12){ persoana.setLuna(persoana.getLuna() -12);}
            writeInDatabase(persoana);

            char s[20];
            system("cls");
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << "V-ati programat cu succes\n";
            SetConsoleTextAttribute(hConsole, 7);
            std::cout << "Numele: " << persoana.getPrenume() << " " << persoana.getNume() << "\n";
            std::cout << "Data: " << persoana.getData() << "." << persoana.getLuna() << "." << date.tm_year+1900 << "\n";
            std::cout << "Vaccinul: " << persoana.getVaccin() << "\n\n";
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << "Press 1 key to continue\n";
            std::cin >> s;
        }
    }else {
        system("cls");
        char answer[100];
        std::cout << "Not such vaccin\n\n";
        std::cout << "1.Try again\n";
        std::cout << "2.Main menu\n\n";
        std::cin >> answer;
        std::cout << "\x1b[1F";
        std::cout << "\x1b[2K";
        while (strcmp(answer, "2")) {
            if (!strcmp(answer, "1")) {
                return 1;
            } else {
                std::cin >> answer;
                std::cout << "\x1b[1F";
                std::cout << "\x1b[2K";
                }
            }
        }
    return 0;
}
void findVaccin(string vaccin){
    system("cls");
    int hasVaccin,error=0;
    std::cout << "Introduceti numele vaccinului\n";
    system("cls");
    hasVaccin = checkIfVaccinInData(vaccin);

    char answer[20];
    if (hasVaccin){
        system("cls");
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "Vaccinul a fost gasit\n\n";
        SetConsoleTextAttribute(hConsole, 15);
    }else{
        system("cls");
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "Vaccinul nu a fost gasit\n\n";
        SetConsoleTextAttribute(hConsole, 15);
    }
    return;
}
rezervare* infoRezervation() {
    rezervare* persoana = (rezervare*)malloc(sizeof(rezervare));
    int exit = 0;
    string tmp;
    time_t t = time(NULL); //Get today time
    struct tm date = *localtime(&t);

    system("cls");
    cout << "Introduceti Prenumele\n";
    cin>>tmp;
    persoana->setPrenume(tmp);

    cout << "Introduceti Numele\n";
    cin>>tmp;
    persoana->setNume(tmp);

    cout << "Introduceti luna\n";
    cin>>tmp;

    while ((stoi(tmp) < 1 || stoi(tmp) > 12) && !exit) {
        system("cls");
        cout << "Incorect month\n";
        cout << "Try again or go to main menu\n";
        cout << "*.Main menu\n";

        cin>>tmp;
        if (tmp == "*")
            exit = 1;
        cout << "\x1b[1F";
        cout << "\x1b[2K";
    }
    if (!exit) persoana->setLuna(stoi(tmp));
    if (!exit){
        cout << "Introduceti Data\n";
        cin>>tmp;
        while ((stoi(tmp) < 1 || stoi(tmp) > dayInMonth(persoana->getLuna())) && !exit){
            system("cls");
            cout << "Incorect date\n";
            cout << "Try again or go to main menu\n";
            cout << "*.Main menu\n";

            cin>>tmp;
            if (tmp=="*")exit=1;
            cout << "\x1b[1F";
            cout << "\x1b[2K";
        }
    }
    if (!exit) persoana->setData(stoi(tmp));
    if (!exit){
        cout << "Introduceti vaccinul\n";
        cin>>tmp;
        persoana->setVaccin(tmp);
    }
    if(exit)persoana=NULL;
    return persoana;
}
int deleteRezervation(rezervare persoana){
    FILE *fp,*fcopy;
    int deleted = 0;
    char row[1000];

    fp = fopen("../rezervare.csv","r");
    fcopy = fopen("../temp.csv","w");
    fputs("Prenume,Nume,Data,Vaccin,",fcopy);

    //Skip names of rows
    fgets(row, 1000, fp);

    while (fgets(row, 1000, fp))
    {
        if (!deleted) {
            char *tmp = strdup(row);
            int isRezervare = !(getfield(tmp, 1) == persoana.getPrenume()) || (getfield(tmp, 2) == persoana.getNume()) ||
            (getfield(tmp, 4) == persoana.getVaccin());
            if (!isRezervare) {
                int size = strlen(row); //Print in file without new line
                if (!strcmp(&row[size-1],"\n")){;
                    row[size-1] = '\0';
                    fputs("\n", fcopy);
                    fputs(row, fcopy);
                }else{
                    fputs("\n", fcopy);
                    fputs(row, fcopy);
                }
            }
            if (isRezervare) deleted = 1;
        }else{
            int size = strlen(row); //Print in file without new line
            if (!strcmp(&row[size-1],"\n")){;
                row[size-1] = '\0';
                fputs("\n", fcopy);
                fputs(row, fcopy);
            }else{
                fputs("\n", fcopy);
                fputs(row, fcopy);
            }
        }
    }
    scanf("some",&row);
    fclose(fp);
    fclose(fcopy);
    std::cout << remove("../rezervare.csv") << std::endl;
    std::cout << rename("../temp.csv", "../rezervare.csv") << std::endl;

    return 0;
}