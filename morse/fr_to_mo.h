#include<iostream>
#include<fstream>
#ifndef FR_TO_MO_H
#define FR_TO_MO_H

bool fichier_texte(std::string file_name);
const char* en_morse(char caractere);
void court (short* donnees_wav, int* top);
void longue(short* donnees_wav, int* top);
void espace_mot (short* donnees_wav, int* top);
void espace_cara (short* donnees_wav, int* top);
void espace_ligne (short* donnees_wav, int* top);
void traduire_fr_mo();

#endif