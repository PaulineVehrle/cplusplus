#include<iostream>
#include<fstream>
#include "fr_to_mo.h"
#include "mo_to_fr.h"

int main(int argc, char* argv[]){
    int a;
    std::cout << "1 : français -> morse" << std::endl;
    std::cout << "2 : morse -> français" << std::endl;
    std::cout << "1 ou 2?"<< std::endl;
    std::cin >> a;

    if (a==1){
        traduire_fr_mo();
    }
    else if (a==2){
        traduire_mo_fr();
    }
    else {
        std::cout << "La valeur rentrée est invalide" << std::endl;
    }    
    return 0;
}