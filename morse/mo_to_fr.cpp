/*Bilan mardi matin. ça marche pas sur la fin quand j'édrit "ef ghij". Il détecte un dernier caractère avec tot_cara = 3.
*/

#include<iostream>
#include<fstream>
#include<string>
#include"wavfile.h"

// vr: vous pourriez ne faire qu'un seule fonction pour fichier_texte et fichier_wav en passant l'extension "wav" ou "txt" en argument
// vr: à la fonction fichier_wav (ou fichier_texte) passez la string par référence pour éviter de recopier l'objet en argument
bool fichier_wav(std::string& file_name){//renvoie True si c'est bien un fichier texte qui est passer, False si c'est juste un texte écrit
    int s=file_name.size();
    bool b = false; // vr: initialisez toujours vos variables
    // vr: utilisez des noms plus parlant pour vos variables b ne veut rien dire (à part boolean ?)
    if (s<4){//la chaine de caractère est trop courte pour qu'il y est une extension
      b = false; // vr: utilisez true et false plutôt que 1 et 0
    }
    else{
        b = (file_name[s-4] == '.') && (file_name[s-3] == 'w') && (file_name[s-2] == 'a') && (file_name[s-1] == 'v'); // onve=érifie que l'extension est bien .txt
    }
    return b;
}

// vr: vous avez codé à la main l'arbre des caractères alphabetiques morses ce n'est pas mal (avec plus de temps pour le projet vous auriez pu construire automatiquement cet arbre)
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

// vr: vous avez écrit un code personnel, c'est vraiment bien, avec plus de temps vous pourriez retravailler ce code pour en faire quelque chose de très bien (avec des classes et des méthodes)
void traduire_mo_fr() {
    std::cout << "Quel fichier à décoder?" << std::endl;
    std::string input;
    std::cin >> input;
    std::cin.get();
    const char * file_name;
    file_name = input.c_str();
    //    if (fichier_wav(file_name))
    // vr: passez la string à la fonction fichier_wav pas le char* sous-jacent
    if (fichier_wav(input)){
        FILE* wavFile = fopen(file_name, "r");
        
        if (wavFile==nullptr){
            std::cout << "Impossible d'ouvrir ce fichier" << std::endl;
        }
        else{

            int longueur = length(wavFile);
            int tableau_donnees[longueur];
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
                    else{
		      //on vient de finir un . ou un - ; on regarde tot_cara pour savoir lequel des 2
		      
		       // vr: ne recalculez pas tout le temps les mêmes choses  (comme ici WAVFILE_SAMPLES_PER_SECOND*0.5*0.251) faites en des attributs/méthodes d'une classe
		      
		      // vr: pourquoi mettez-vous & pour tester toto_cara ? c'est && ou and
		      // vr: ici on préfèrerais lire "if (truc.est_un_point(toto_cara)"
                        if ((toto_cara<WAVFILE_SAMPLES_PER_SECOND*0.5*0.251) and (toto_cara>WAVFILE_SAMPLES_PER_SECOND*0.5*0.245)){//On vient d'etendre un . ; on met simplement une égalité car s'il y a un léger problème de comptage, on traduira bien quand même

                            caractere_courant[top]=1;
                            top = top +1;
                            toto_cara=0;
                            dans_un_espace=1;//on est dans un espace. Un grand nombre de caractère suivant seront nuls.
                        }
			// vr: idem & est and
			// vr: on préfèrerais lire if (est_un_trait(toto_cara)
                        else if ((toto_cara<WAVFILE_SAMPLES_PER_SECOND*0.5*1.01) and (toto_cara>WAVFILE_SAMPLES_PER_SECOND*0.5*0.99)) {//on vient d'entendre un -
                            caractere_courant[top]=2;
                            top = top +1;
                            toto_cara=0;
                            dans_un_espace=1;//on est dans un espace. Un grand nombre de caractère suivant seront nuls.
                        }
                        else {//on n'a pas réellement finit un caractère . ou - car il n'a pas duré la bonne longueur
                            toto_espace = toto_espace +1;
                        }
                    }
                }
                else{//les 2 derniers caractères ne sont pas tous les deux nuls
                    if (dans_un_espace){//on vient de finir un espace.On regarde tot_espace pour connaitre le type d'espace
                        if (toto_espace<WAVFILE_SAMPLES_PER_SECOND*0.5*0.1){//plus petit espace => espace entre 2 sons
                        }
                        else if ((toto_espace>WAVFILE_SAMPLES_PER_SECOND*0.5*0.15) and (toto_espace<WAVFILE_SAMPLES_PER_SECOND*0.5*0.6)){//espace entre 2 caractères
			  // vr: le code suivant est dupliqué 3 fois avec très peu de changements, il faut que vous factorisiez (découpiez) votre code

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
                            caractere_courant[0]=0;//le caractère qu'on est en train  de décoder repart de 0
                            caractere_courant[1]=0;
                            caractere_courant[2]=0;
                            caractere_courant[3]=0;
                            top=0;
			    // vr: seule code différent pour ce if
                            std::cout << " ";
                            fichier_texte << ' ';

                        }
                        else {//espace entre 2 paragraphes
                            char c = caractere(caractere_courant);
                            fichier_texte << c;
                            std::cout << c;
                            caractere_courant[0]=0;//le caractère qu'on est en train  de décoder repart de 0
                            caractere_courant[1]=0;
                            caractere_courant[2]=0;
                            caractere_courant[3]=0;
                            top=0;
			    // vr: seule code différent pour ce if
                            std::cout << '\n';
                            fichier_texte << '\n';
                        }
                        toto_espace = 0;
                        dans_un_espace=0;
                    }
                    else{
                        toto_cara = toto_cara +1;
                    }
                }
            }

            if (top!=0){//si le dernier caractère n'a pas été mis ajouter (car on n'est pas reparti sur un espace)
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
