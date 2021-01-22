//fichier qui permet de créer un wavfile. Il permet aussi d'écrire dans le fichier, en lui donnant un tableau de short

#include "wavfile.h"
#include<iostream>
#include <string>
#include <fstream>
#include <cstdint>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wavfile_header {
	char	riff_tag[4];
	int	riff_length;
	char	wave_tag[4];
	char	fmt_tag[4];
	int	fmt_length;
	short	audio_format;
	short	num_channels;
	int	sample_rate;
	int	byte_rate;
	short	block_align;
	short	bits_per_sample;
	char	data_tag[4];
	int	data_length;
};

FILE * wavfile_open( const char *filename )
{
	struct wavfile_header header;

	int samples_per_second = WAVFILE_SAMPLES_PER_SECOND*0.5;
	int bits_per_sample = 16;

	strncpy(header.riff_tag,"RIFF",4);
	strncpy(header.wave_tag,"WAVE",4);
	strncpy(header.fmt_tag,"fmt ",4);
	strncpy(header.data_tag,"data",4);

	header.riff_length = 0;
	header.fmt_length = 16;
	header.audio_format = 1;
	header.num_channels = 1;
	header.sample_rate = samples_per_second;
	header.byte_rate = samples_per_second*(bits_per_sample/8);
	header.block_align = bits_per_sample/8;
	header.bits_per_sample = bits_per_sample;
	header.data_length = 0;

	FILE * file = fopen(filename,"wb+");
	if(!file) return 0;

	fwrite(&header,sizeof(header),1,file);

	fflush(file);

	return file;

}

void wavfile_write( FILE *file, short data[], int length )
{
	fwrite(data,sizeof(short),length,file);
}

void wavfile_close( FILE *file )
{
	int file_length = ftell(file);

	int data_length = file_length - sizeof(struct wavfile_header);
	fseek(file,sizeof(struct wavfile_header) - sizeof(int),SEEK_SET);
	fwrite(&data_length,sizeof(data_length),1,file);

	int riff_length = file_length - 8;
	fseek(file,4,SEEK_SET);
	fwrite(&riff_length,sizeof(riff_length),1,file);

	fclose(file);
}


void wavfile_read (FILE *wavFile, int* tableau_donnees){
	wavfile_header header;
	int headerSize = sizeof(wavfile_header);
	int filelength = 0;
	size_t bytesRead = fread(&header, 1, headerSize, wavFile);
	int top = 0;
	if (bytesRead > 0){
        uint16_t bytesPerSample = header.bits_per_sample / 8;
        uint64_t numSamples = (36 + header.data_length *2) / bytesPerSample;
        static const uint16_t BUFFER_SIZE = 2;
        int8_t* buffer = new int8_t[BUFFER_SIZE];
        while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
        {
			int a = int((unsigned char)(buffer[0]) << 24 |
            (unsigned char)(buffer[1]) << 16 |
            (unsigned char)(buffer[2]) << 8 |
            (unsigned char)(buffer[3]));
			tableau_donnees[top]=a;
			top=top+1;
        }
        delete [] buffer;
        buffer = nullptr;
        filelength = getFileSize(wavFile);

	}
}

int getFileSize(FILE* inFile)
{
    int fileSize = 0;
    fseek(inFile, 0, SEEK_END);

    fileSize = ftell(inFile);

    fseek(inFile, 0, SEEK_SET);
    return fileSize;
}

int length(FILE *wavFile ){
	wavfile_header header;
	int headerSize = sizeof(wavfile_header);
	int filelength = 0;
	size_t bytesRead = fread(&header, 1, headerSize, wavFile);
	int top = 0;
	if (bytesRead > 0){
        uint16_t bytesPerSample = header.bits_per_sample / 8;
        uint64_t numSamples = (36 + header.data_length *2) / bytesPerSample;
        static const uint16_t BUFFER_SIZE = 2;
        int8_t* buffer = new int8_t[BUFFER_SIZE];
        while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
        {
			int a = int((unsigned char)(buffer[0]) << 24 |
            (unsigned char)(buffer[1]) << 16 |
            (unsigned char)(buffer[2]) << 8 |
            (unsigned char)(buffer[3]));
			top=top+1;
        }
        delete [] buffer;
        buffer = nullptr;
        filelength = getFileSize(wavFile);

	}
	return top;
}