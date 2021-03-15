#include<iostream>
#include<fstream>
#include "fr_to_mo.h"
#include "mo_to_fr.h"

// vr: vous avez oublié de mettre le Makefile dans votre repo

// vr: ne mettez pas de code directement dans le main mais appelez-y des fonctions
void menu_morse_to_wav () {
  std::cout << "1 : français -> morse" << std::endl;
  std::cout << "2 : morse -> français" << std::endl;
  std::cout << "1 ou 2?"<< std::endl;
  // vr: mettez les definitions des variables au plus proche de leur utilisation
  int a;
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
}

int main(int argc, char* argv[]){
  menu_morse_to_wav();
    return 0;
}
