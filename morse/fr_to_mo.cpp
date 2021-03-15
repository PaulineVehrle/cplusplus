#include<iostream>
#include<fstream>
#include<string>
#include <math.h>
#include <string.h>
#include "wavfile.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <errno.h>


// vr: voir les commentaires de la fonction fichier_wav
bool fichier_texte(std::string file_name){//renvoie True si c'est bien un fichier texte qui est passer, False si c'est juste un texte écrit
    int s=file_name.size();
    bool b;
    if (s<4){//la chaine de caractère est trop courte pour qu'il y est une extension
        b = 0;
    }
    else{
        b = (file_name[s-4] == '.') && (file_name[s-3] == 't') && (file_name[s-2] == 'x') && (file_name[s-1] == 't'); // onve=érifie que l'extension est bien .txt
    }
    return b;
}

const char* en_morse(char caractere){// renvoie la valeur morse d'un caractère donné en entrée
    //on crée des listes avec les correspondances français<->morse
  // vr: c'est bien la constante static dans une fonction, mais on préfèrerait une classe pour ranger cela avec les méthodes qui s'appliquent 
  // vr: vous auriez pu utiliser une std::map
    static const char *morse[27] = {".-", "-...", "-.-.", "-..", ".","..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."," "};
    static const char alph[] = {'a', 'b', 'c', 'd', 'e', 'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};

    int entier = caractere;//on recuperer le code ascii de la lettre
    // pas & mais and
    if ((entier>64) and (entier<91)){//la lettre est une majuscule
      // vr: utilisez 'A' à la place de 64 c'est plsu lisible
        entier=entier-65;
    }
    if ((entier>96) and (entier<123)){//la lettre est une minuscule
        entier=entier-97;
    }
    if (entier==32){
        entier = 26;
    }
    const char* valeur_morse;
    valeur_morse = morse[entier];
    return valeur_morse;
}

void court (short* donnees_wav, int* top){// on ajoute un son court au fichier
  //vr: là encore évitez de toujours recalculer les mêmes choses
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*0.5*0.25);
    const int NUM_SAMPLES_espace = (WAVFILE_SAMPLES_PER_SECOND*0.5*0.05);
	double frequency = 440.0;
	int volume = 32000;
	int length = NUM_SAMPLES;
    int length_espace = NUM_SAMPLES_espace;
	int i;// on crée une sinusoide à 440 Hz pendant le temps désiré
	for(i=0;i<length;i++) {
		double t = (double) i *2 / WAVFILE_SAMPLES_PER_SECOND;
		donnees_wav[*top + i] = volume*sin(frequency*t*2*M_PI);
	}

    for(i=length;i<length_espace;i++) {//on ajoute un petit silence après chaque son (court ou long) pour pouvoir les differencier
		double t = (double) i *2 / WAVFILE_SAMPLES_PER_SECOND;
		donnees_wav[*top + i] = 0;
	}

    *top = *top + length+length_espace;

}

void longue(short* donnees_wav, int* top){// on ajoute un son long au fichier
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*0.5*1);
    const int NUM_SAMPLES_espace = (WAVFILE_SAMPLES_PER_SECOND*0.5*0.05);
	double frequency = 440.0;
	int volume = 32000;
	int length = NUM_SAMPLES;
    int length_espace = NUM_SAMPLES_espace;

	int i;// on crée une sinusoide à 440 Hz pendant le temps désiré
	for(i=0;i<length;i++) {
		double t = (double) i *2 / WAVFILE_SAMPLES_PER_SECOND;
		donnees_wav[(*top) + i] = volume*sin(frequency*t*2*M_PI);
	}

    for(i=length;i<length_espace;i++) {
		double t = (double) i *2 / WAVFILE_SAMPLES_PER_SECOND;
		donnees_wav[*top + i] = 0;
	}

	*top = *top + length+length_espace;

}

void espace_mot (short* donnees_wav, int* top){// on ajoute un espace après un mot au fichier
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*0.5*0.7);
	double frequency = 440.0;
	int volume = 0;
	int length = NUM_SAMPLES;

	int i;// on crée une sinusoide à 440 Hz pendant le temps désiré
	for(i=0;i<length;i++) {
		double t = (double) i*2 / WAVFILE_SAMPLES_PER_SECOND;
		donnees_wav[*top + i] = volume*sin(frequency*t*2*M_PI);
	}

	*top = *top + length;

}

void espace_cara (short* donnees_wav, int* top){// on ajoute un espace après un caractère au fichier. Cet espace est plus court que celui entre 2 mots, afin de les différencier
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*0.5*0.5);
	double frequency = 440.0;
	int volume = 0;
	int length = NUM_SAMPLES;

	int i;// on crée une sinusoide à 440 Hz pendant le temps désiré
	for(i=0;i<length;i++) {
		double t = (double) i *2 / WAVFILE_SAMPLES_PER_SECOND;
		donnees_wav[*top + i] = volume*sin(frequency*t*2*M_PI);
	}

	*top = *top + length;
}

void espace_ligne (short* donnees_wav, int* top){// on ajoute un espace après une ligne au fichier. Cet espace est plus court que celui entre 2 mots, afin de les différencier
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*0.5*1.3);
	double frequency = 440.0;
	int volume = 0;
	int length = NUM_SAMPLES;

	int i;// on crée une sinusoide à 440 Hz pendant le temps désiré
	for(i=0;i<length;i++) {
		double t = (double) i *2 / WAVFILE_SAMPLES_PER_SECOND;
		donnees_wav[*top + i] = volume*sin(frequency*t*2*M_PI);
	}

	*top = *top + length;
}

void traduire_fr_mo(){

    //récupération du fichier à traduire
    std::string x;
    std::getline(std::cin,x);
    std::cout << "Quoi traduire ? (attention, sans accents)" << std::endl;
    std::string file_name;
    std::getline(std::cin, file_name);


    bool b = 0;//b=False si on a passé directement un fichier texte, b=True sinon
    if (!(fichier_texte(file_name))){//si on a pas passé un fichier texte, on transforme le texte passé en un fichier texte pour ne plus avoir de disjonction de cas
        std::ofstream fichier_creer;
        fichier_creer.open("traduire.txt");
        fichier_creer << file_name << std::endl;
        file_name = "traduire.txt";
        b = 1;
    }

    std::ifstream fichier (file_name);//pour lire le fichier
    std::string ligne { "" };
    int longueur = 0;//longueur = longueur du tableau de données qu'on va ajouter au wav file
    int li = 0;//compteur du nombre de ligne, utile si on a un fichier texte en entrée

    bool not_espace = 1;

    if (fichier){
    //on parcourt une première fois le texte pour savoir la longueur de données qu'il va falloir passer pour la création du fichier wav
        while (!fichier.eof()){ //eof est le flag de fin de fichier il se met a 1 quand la fin du fichier est atteinte.  
            getline(fichier,ligne); 
            li = li +1;
            for(int i=0;i<ligne.length();i++) {
                const char* code = en_morse(ligne[i]);
                int s = strlen(code);
                for (int j=0;j<s;j++){
                    char c = code[j];
                    if (c=='.'){
                        longueur = longueur + WAVFILE_SAMPLES_PER_SECOND*0.5*0.3;
                    }
                    else if (c=='-'){
                        longueur = longueur + WAVFILE_SAMPLES_PER_SECOND*0.5*1.05;
                    }
                    else if (c==' '){
                        longueur = longueur + WAVFILE_SAMPLES_PER_SECOND*0.5*0.7;
                        not_espace=0;
                    }
                }
                if (not_espace){
                    longueur = longueur + WAVFILE_SAMPLES_PER_SECOND*0.5*0.5;
                }
                else{
                    not_espace=1;
                }
                
            }
        }

        if (b){
            li=1;
        }

        if (li > 1){//on intègre des retours à la ligne seulement s'il y a plusieurs lignes
            longueur = longueur + WAVFILE_SAMPLES_PER_SECOND*0.5*1.3*(li-1);
        }

        short donnees_wav[longueur];//tableau vide où on va mettre les données
        int top=0;
        int li2 = 0;

        fichier.clear();//on remet à 0 pour pouvoir reparcourir la liste
        fichier.seekg(0, std::ios::beg);

        not_espace = 1;

    //on reparcourt le texte pour le transformer données dans "donnees_wav"
        while (!fichier.eof()){ 
            getline(fichier,ligne);
            li2 = li2 +1;
            for(int i=0;i<ligne.length();i++) { 
                const char* code = en_morse(ligne[i]);
                int s = strlen(code);
                for (int j=0;j<s;j++){
                    char c = code[j];
                    if (c=='.'){
                        court(donnees_wav,&top);
                    }
                    else if (c=='-'){
                        longue(donnees_wav,&top);
                    }
                    else if (c==' '){
                        espace_mot(donnees_wav,&top);
                        not_espace=0;
                    }
                }
                if (not_espace){
                    espace_cara(donnees_wav,&top);
                }
                else{
                    not_espace=1;
                }

            }
            if ((li!=li2) & (b==0)){
                espace_ligne(donnees_wav,&top);
            }
        }

    //on crée le fichier wav qui sera notre traduction 
        FILE * fichier_traduction = wavfile_open("traduction.wav");

    //on écrit notre liste de données dans le fichier wav créé
        wavfile_write(fichier_traduction,donnees_wav,longueur);
        wavfile_close(fichier_traduction);

        if (b){//on efface le fichier texte qui a été créé (si on n'avait pas passé un fichier texte directement)
            remove("traduire.txt");
        }
        std::cout << "Le texte traduit se trouve dans le fichier 'traduction.wav'" << std::endl;
    }

    else {
        std::cout << "Le fichier n'a pas pu être ouvert" << std::endl;
    }


}       
