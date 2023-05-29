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
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
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
    return "";
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
    ofstream fpt;
    string row;
    if(file_exists("../rezervare.csv")){
        fpt.open("../rezervare.csv", ios::app);
        fpt << "\n" << persoana.getPrenume() << "," << persoana.getNume() << "," << persoana.getData() << "." << persoana.getLuna() << "," << persoana.getVaccin() << ",";
        fpt.close();
    } else{
        fpt.open("../rezervare.csv", ios::app);
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
    ifstream fp;
    string row,center;
    string avaliableCenter[9];
    int i=0;

    fp.open("../data.csv");
    cin.ignore();
    getline(fp, row);

    if(!fp.eof()){cout << "Alegeti centrul:\n\n";}
    while (!fp.eof()) {
        getline(fp, row);
        if (row.find(vaccin) != string::npos && i<10) {
            avaliableCenter[i] = row;
            cout << i + 1 << "." << row << endl;
            i++;
        }
    }
    cout << i + 1 << ".Inapoi\n";

    string answer;
    cin >> answer;
    if (stoi(answer) == 0 || stoi(answer)>i+1){
        while(stoi(answer) == 0 || stoi(answer)>i){
            std::cin >> answer;
            std::cout << "\x1b[1F";
            std::cout << "\x1b[2K";
        };
    }else if (stoi(answer) == i+1) {
        return "Back";
    }
    fp.close();
    return avaliableCenter[stoi(answer)-1];
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

    while (!checkIfVaccinInData(persoana.getVaccin() )){
        system("cls");
        cout << "Not such vaccin\n\n";
        cout << "1.Try again\n";
        cout << "2.Main menu\n\n";
        cin >> tmp;
        cout << "\x1b[1F";
        cout << "\x1b[2K";
        if (tmp == string("2")) {
            break;
        }else if(tmp == string("1")){
            system("cls");
            cout << "Introduceti vaccinul: ";
            cin >> tmp;
            persoana.setVaccin(tmp);
            cout << "\x1b[1F";
            cout << "\x1b[2K";
        }
    }

    if (checkIfVaccinInData(persoana.getVaccin() )){
        system("cls");
        persoana.setCentrul(chooseCenter(persoana.getVaccin()) );
        system("cls");
        if (persoana.getCentrul()!="Back"){//If center exist
            time_t t = time(NULL);//Get today time
            struct tm date = *localtime(&t);
            string readData;
            int dataNow = date.tm_mday+1;
            int monthNow = date.tm_mon+1;
            int monthNext = date.tm_mon+2;

            if (monthNext > 12)monthNext-=12;
            int dataNext = dataNow-1;
            cout << "Alegeti doar data " << dataNow << "." << monthNow << "-" << dataNext << "." << monthNext << std::endl;
            cin >> readData;// Read date of rezervation
            cout << "\x1b[1F";
            cout << "\x1b[2K";

            while (stoi(readData) < 1 || stoi(readData) > dayInMonth(date.tm_mon)){
                system("cls");
                cout << "Incorect date\n";

                cin >> readData;
                cout << "\x1b[1F";
                cout << "\x1b[2K";
            }
            persoana.setData(stoi(readData));
            if (persoana.getData() > date.tm_mday){
                persoana.setLuna(date.tm_mon + 1);
            }else{
                persoana.setLuna( date.tm_mon + 2);
            }
            if(persoana.getLuna() > 12){ persoana.setLuna(persoana.getLuna() -12);}
            writeInDatabase(persoana);


            system("cls");

            SetConsoleTextAttribute(hConsole, 10);
            cout << "V-ati programat cu succes\n";
            SetConsoleTextAttribute(hConsole, 7);
            cout << "Numele: " << persoana.getPrenume() << " " << persoana.getNume() << "\n";
            cout << "Data: " << persoana.getData() << "." << persoana.getLuna() << "." << date.tm_year+1900 << "\n";
            cout << "Vaccinul: " << persoana.getVaccin() << "\n\n";

            SetConsoleTextAttribute(hConsole, 14);
            cout << "Press 1 key to continue\n";
            string s;
            cin >> s;
            SetConsoleTextAttribute(hConsole, 15);
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
    rezervare* persoana = new rezervare[1];
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

    while ((!is_number(tmp) || stoi(tmp) < 1 || stoi(tmp) > 12) && !exit) {
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
        while ((!is_number(tmp) || stoi(tmp) < 1 || stoi(tmp) > dayInMonth(persoana->getLuna())) && !exit){
            system("cls");
            cout << "Incorect date\n";
            cout << "Try again or go to main menu\n";
            cout << "*.Main menu\n";

            cin>>tmp;
            if (tmp==string("*"))exit=1;
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
    ifstream fp;
    ofstream fcopy;
    int deleted = 0;
    string row;

    fp.open("../rezervare.csv");
    fcopy.open("../temp.csv");
    fcopy<<"Prenume,Nume,Data,Vaccin,";

    //Skip names of rows
    getline(fp, row);

    while (getline(fp, row))
    {
        if (!deleted) {
            string tmp = row;

            bool isRezervare = getfield(tmp, 1) == persoana.getPrenume() && getfield(tmp, 2) == persoana.getNume() &&
            getfield(tmp, 4) == persoana.getVaccin();
            cout<<isRezervare;
            if (!isRezervare) {
                int size = row.length(); //Print in file without new line
                if (!strcmp(&row[size-1],"\n")){;
                    row[size-1] = '\0';
                    fcopy<<"\n";
                    fcopy<<row;
                }else{
                    fcopy<<"\n";
                    fcopy<<row;
                }
            }
            if (isRezervare) deleted = 1;
        }else{
            int size = row.size(); //Print in file without new line
            if (!strcmp(&row[size-1],"\n")){;
                row[size-1] = '\0';
                fcopy<<"\n";
                fcopy<<row;
            }else{
                fcopy<<"\n";
                fcopy<<row;
            }
        }
    }
    fp.close();
    fcopy.close();
    cout << remove("../rezervare.csv") << std::endl;
    cout << rename("../temp.csv", "../rezervare.csv") << std::endl;

    return 0;
}