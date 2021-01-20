//fichier récupérer

#ifndef WAVFILE_H
#define WAVFILE_H

#include <stdio.h>
#include <inttypes.h>

FILE * wavfile_open( const char *filename );
void wavfile_write( FILE *file, short data[], int length );
void wavfile_close( FILE * file );
void wavfile_read (FILE *file, int* tableau_donnees);
int getFileSize(FILE* inFile);
int length(FILE* inFile);

#define WAVFILE_SAMPLES_PER_SECOND 44100

#endif