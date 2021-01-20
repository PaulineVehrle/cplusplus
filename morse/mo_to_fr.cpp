/*Bilan mardi matin. ça marche pas sur la fin quand j'édrit "ef ghij". Il détecte un dernier caractère avec tot_cara = 3.
*/
#include<iostream>
#include<fstream>
#include<string>
#include"wavfile.h"

bool fichier_wav(std::string file_name){//renvoie True si c'est bien un fichier texte qui est passer, False si c'est juste un texte écrit
    int s=file_name.size();
    bool b;
    if (s<4){//la chaine de caractère est trop courte pour qu'il y est une extension
        b = 0;
    }
    else{
        b = (file_name[s-4] == '.') && (file_name[s-3] == 'w') && (file_name[s-2] == 'a') && (file_name[s-1] == 'v'); // onve=érifie que l'extension est bien .txt
    }
    return b;
}

char caractere(int tableau[]){//donne le caractère entendu en morse
    //std::cout << "tableau[0] = " << tableau[0] << std::endl;
        if (tableau[0]==1){//.???
        if (tableau[1]==1){//..??
            if (tableau[2]==1){//...?
                if (tableau[3]==1){//....
                    return 'h';
                }
                else if (tableau[3]==2){//...-
                    return 'v';
                }
                else{//...
                    return 's';
                }
            }
            else if (tableau[2]==2){//..-?
                if (tableau[3]==1){//..-.
                    return 'f';
                }
                else{//..-
                    return 'u';
                }
            }
            else {//..
                return 'i';
            }
        }
        else if(tableau[1]==2){//.-??
            if (tableau[2]==1){//.-.?
                if (tableau[3]==1){//.-..
                    return 'l';
                }
                else{//.-.
                    return 'r';
                }
            }
            else if (tableau[2]==2){//.--?
                if (tableau[3]==1){//.--.
                    return 'p';
                }
                else if (tableau[3]==2){//.---
                    return 'j';
                }
                else{//.--
                    return 'w';
                }
            }
            else {//.-
                return 'a';
            }
        }
        else {//.
            return 'e';
            std::cout << "hé ho" << std::endl;
        }
    }
    else{//-???
       if (tableau[1]==1){//-.??
            if (tableau[2]==1){//-..?
                if (tableau[3]==1){//-...
                    return 'b';
                }
                else if (tableau[3]==2){//-..-
                    return 'x';
                }
                else{//-..
                    return 'd';
                }
            }
            else if (tableau[2]==2){//-.-?
                if (tableau[3]==1){//-.-.
                    return 'c';
                }
                else if (tableau[3]==2){//-.--
                    return 'y';
                }
                else{//-.-
                    return 'k';
                }
            }
            else {//-.
                return 'n';
            }
        }
        else if(tableau[1]==2){//--??
            if (tableau[2]==1){//--.?
                if (tableau[3]==1){//--..
                    return 'z';
                }
                else if (tableau[3]==2){//--.-
                    return 'q';
                }
                else{//--.
                    return 'g';
                }
            }
            else if (tableau[2]==2){//---
                return 'o';
            }
            else {//--
                return 'm';
            }
        }
        else {//-
            return 't';
        } 
    }
}

void traduire_mo_fr() {
    std::cout << "Quel fichier à décoder?" << std::endl;
    std::string input;
    std::cin >> input;
    std::cin.get();
    const char * file_name;
    file_name = input.c_str();
    if (fichier_wav(file_name)){
        FILE* wavFile = fopen(file_name, "r");
        
        if (wavFile==nullptr){
            std::cout << "Impossible d'ouvrir ce fichier" << std::endl;
        }
        else{
            int longueur = length(wavFile);
            std::cout << longueur << std::endl;
            int tableau_donnees [longueur];
            wavfile_read(wavFile, tableau_donnees);
            std::ofstream fichier_texte;
            fichier_texte.open("traduction.txt");
            
            int toto_cara=0;
            int toto_espace=0;
            bool dans_un_espace =0;
            int caractere_courant[4]={0,0,0,0};//on mettra 1 pour un . et 2 pour un -
            int top =0;//compris entre 0 et 3, correspond à la case dans laquelle on est en train d'écrire dans le caractère courant

            for (int i=1;i<longueur;i++){
                if ((tableau_donnees[i]==0) and (tableau_donnees[i-1]==0)){//on va tomper sur un moment de silence
                    if (dans_un_espace){//on est déjà dans un espace. On augmente simplement le compteur d'espace
                        toto_espace = toto_espace +1;
                    }
                    else{//on vient de finir un . ou un -
                        //std::cout << std::boolalpha << dans_un_espace << std::endl;
                        //si toto_cara=11025, c'est un . ; si toto_cara=44100,c'est un -
                        if ((toto_cara<WAVFILE_SAMPLES_PER_SECOND*0.5*0.251) & (toto_cara>WAVFILE_SAMPLES_PER_SECOND*0.5*0.245)){//on met simplement une égalité car s'il y a un léger problème de comptage, on traduira bien quand même
                            caractere_courant[top]=1;
                            //std::cout << "toto_cara court = " << toto_cara << std::endl;
                            top = top +1;
                            toto_cara=0;
                            dans_un_espace=1;//on est dans un espace. Un grand nombre de caractère suivant seront nuls.
                            //std::cout <<"caractere_courant[" << top << "] = " << caractere_courant[top] << std::endl;
                        }
                        else if ((toto_cara<WAVFILE_SAMPLES_PER_SECOND*0.5*1.01) & (toto_cara>WAVFILE_SAMPLES_PER_SECOND*0.5*0.99)) {
                            //std::cout << "toto_cara long = " << toto_cara << std::endl;
                            caractere_courant[top]=2;
                            top = top +1;
                            toto_cara=0;
                            dans_un_espace=1;//on est dans un espace. Un grand nombre de caractère suivant seront nuls.
                            //std::cout <<"caractere_courant[" << top << "] = " << caractere_courant[top] << std::endl;
                        }
                        else {//c'est juste le bug
                            toto_espace = toto_espace +1;
                        }
                        //std::cout << "toto_cara = " << toto_cara << std::endl;
                        //std::cout << std::boolalpha << dans_un_espace << std::endl;
                    }
                }
                else{//les 2 derniers caractères ne sont pas tous les deux nuls
                    if (dans_un_espace){//on vient de finir un espace. si toto_espace=2205 => espace entre 2 sons. Si toto_espace=22050 + 2205 => espace entre 2 caractères. Si toto_espace=44100+2205 => espace entre 2 mots.
                        if (toto_espace<WAVFILE_SAMPLES_PER_SECOND*0.5*0.1){//espace entre 2 sons
                        }
                        else if ((toto_espace>WAVFILE_SAMPLES_PER_SECOND*0.5*0.15) and (toto_espace<WAVFILE_SAMPLES_PER_SECOND*0.5*0.6)){//espace entre 2 caractères
                            char c = caractere(caractere_courant);
                            fichier_texte << c;
                            std::cout << c;
                            caractere_courant[0]=0;//le caractère qu'on est en train  de décoder repart de 0
                            caractere_courant[1]=0;
                            caractere_courant[2]=0;
                            caractere_courant[3]=0;
                            top=0;
                        }
                        else if ((toto_espace>WAVFILE_SAMPLES_PER_SECOND*0.5*0.65) and (toto_espace<WAVFILE_SAMPLES_PER_SECOND*0.5*1.8)){//espace entre 2 mots
                            char c = caractere(caractere_courant);
                            fichier_texte << c;
                            std::cout << c;
                            std::cout << " ";
                            caractere_courant[0]=0;//le caractère qu'on est en train  de décoder repart de 0
                            caractere_courant[1]=0;
                            caractere_courant[2]=0;
                            caractere_courant[3]=0;
                            fichier_texte << ' ';
                            top=0;
                        }
                        else {//espace entre 2 paragraphes
                            char c = caractere(caractere_courant);
                            fichier_texte << c;
                            std::cout << c;
                            std::cout << '\n';
                            caractere_courant[0]=0;//le caractère qu'on est en train  de décoder repart de 0
                            caractere_courant[1]=0;
                            caractere_courant[2]=0;
                            caractere_courant[3]=0;
                            fichier_texte << '\n';
                            top=0;
                        }
                        //std::cout << "toto_espace = " << toto_espace << std::endl; 
                        toto_espace = 0;
                        //std::cout << std::boolalpha << dans_un_espace << std::endl;
                        dans_un_espace=0;
                        //std::cout << std::boolalpha << dans_un_espace << std::endl;
                    }
                    else{
                        toto_cara = toto_cara +1;
                    }
                }
            }
            //std::cout << "top = " << top << std::endl;
            if (top!=0){
                char c = caractere(caractere_courant);
                fichier_texte << c;
                std::cout << c;
            }

            std::cout << "" << std::endl;
            fclose(wavFile);
            std::cout << "La traduction a également été mise dans le fichier traduction.txt" << std::endl;
        }
    }
    else{
        std::cout << "c'est pas un fichier wav" << std::endl;
    }
    
}