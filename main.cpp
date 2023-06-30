#include<iostream>
#include<string>

#include "clases/rezervare.h"
#include "modules/afisare.h"
#include "modules/programare.h"

using namespace std;
void runFromConsole(char *argv[],int &error){
    if(argv[1]==string("-show")){
        showCenters(false);
    }else if(argv[1] == string("-find")){
        if (argv[2]!=NULL)findVaccin(argv[2],false);
        else cout<<"Scrieti numele vaccinului";
    }else if(argv[1] == string("-program")){
        programare();
    }else if(argv[1] == string("-delete")){
        rezervare *rezervation = infoRezervation();
        if(rezervation!=NULL)deleteRezervation(*rezervation);
    }else {
        error = 1;
    }
}
void runFromExe(){
    int error=0;
    string answer;
    while (answer != string("*")){
        system("cls");
        start();
        if (error){
            cout<<"\nInvalid input\nTry again"<<endl;
            error = 0;
        }

        cin>>answer;
        if(answer == string("1")){
            showCenters(true);
        }else if(answer == string("2")){
            string vaccin;
            findVaccin(vaccin,true);
        }else if(answer == string("3")){
            int reProgram;
            reProgram = programare();
            while(reProgram){
                reProgram = programare();//facem reprogramarea in caz ca a aparut dificultati
            }
        }else {
            error = 1;
        }

    }
}
int main(int arg,char *argv[]){
    int error=0;

    if(arg == 1){
        runFromExe();
    }else{
        runFromConsole(argv,error);
    }


    return 0;
}