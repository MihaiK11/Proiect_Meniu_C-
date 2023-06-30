#include "afisare.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
void showCenters(bool fromExe){
    string answer;
    system("cls");
    cout << "Centrele:\n";
    readAndShowData();
    if (fromExe){
        cout<<"\n\n*.Enter any key to return to main menu\n\n";
        cin>>answer;
    }
    return;
}
int readAndShowData(){

    FILE *fp;
    char row[1000];

    fp = fopen("../data.csv","r");
    fgets(row, 1000, fp);
    while (!feof(fp))
    {
        fgets(row, 1000, fp);
        std::cout << row;
    }
    fclose(fp);

    return 0;
}