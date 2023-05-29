#include<iostream>
#include<string>

#include "clases/rezervare.h"
#include "modules/afisare.h"
#include "modules/programare.h"

using namespace std;

int main(int arg,char *argv[]){
    int error=0;
    string answer;
    if(argv[1]==string("-show")){
        showCenters();
    }else if(argv[1] == string("-find")){
        if (argv[2]!=NULL)findVaccin(argv[2]);
        else cout<<"Scrieti numele vaccinului";
    }else if(argv[1] == string("-program")){
        int reProgram=0;
        reProgram = programare();
        while(reProgram){
            reProgram = programare();//facem reprogramarea in caz ca a aparut dificultati
        }
    }
//        }else if(argv[1] == "4"){
//            rezervare *rezervation = infoRezervation();
//            if(rezervation!=NULL)deleteRezervation(*rezervation);
//        }else {
//            error = 1;
//        }
//
//    }

    return 0;
}