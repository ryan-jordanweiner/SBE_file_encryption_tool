#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "encryption.h"
#include "encryption.c"

#define MAX_FILENAME_LEN (81)

int getFileSize(FILE *fptr);
void readData(unsigned char* data, FILE *fptr);
void outputToFile(char* filename, int size, unsigned char* data);

//driver file, might split up into a few different routines or files later
int main(int argc, char *args[]) {
	FILE *fptr;
	//open file
	fptr = fopen(args[2], "r");
	if (fptr == NULL) //Check for file not available
	{
		printf("Cannot open file \n");
		exit(0);
	}

	/*
	 *calculate size of file;
	 */
	int size = getFileSize(fptr);

	/*
	 * read file contents into data 
	 * contains file contents as is  until (de)encryption routine
	 * size dynamically according to the size of the file being read
	 */
	unsigned char* data = (unsigned char*) malloc((size + 1));

	//read data into memory
	readData(data, fptr);
	*(data + size) = '\0';
	//close file
        fclose(fptr);
	
	/*data now contains the contents of the file passed through the command line*/
	
	//create filename for output
	//filename length:
	//
	
	char filename[MAX_FILENAME_LEN];	
	if (argc == 4) {
		strcpy(filename, args[3]);
	
	}	
	else {
		int i = 0;
		while (args[2][i] != '.') {
			filename[i] = args[2][i];
			i++;
		}
		filename[i++] = '_';
		int d = i;
		if (!(strcmp(args[1], "-e"))) {
			filename[i++] = 'E';
		}
		if (!(strcmp(args[1], "-d"))) {
			filename[i++] = 'D';
		}
		filename[i++] = '.';
		while (args[2][d] != '\0') {
			filename[i++] = args[2][d++];
		}
		filename[i] = '\0';
	}
	if (!(strcmp(args[1], "-e"))) {
		encrypt_data(data, size);
		//encrypt_chunked(data, size);
	}
	if (!(strcmp(args[1], "-d"))) {
		decrypt_data(data, size);
	}

	printf("(de)encrypted file: %s\n", filename);
	//log to output file
	outputToFile(filename, size, data);

	return 0;
}


/*
 * calculate the size of the file by using the difference in memory address between the end of the file and the beginning of the file;
 */
int getFileSize(FILE* fptr) {
	fseek(fptr, 0, SEEK_END);
        unsigned long size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);
        size -= ftell(fptr);
	size += (4-size%4);
	return size;
}

/*
 * read data from file into memory at data
 */
void readData(unsigned char* data, FILE* fptr) {
	char c = '0';
        int i = 0;
        //read data into the  memory allocation
        while (c != EOF)
        {
                c = fgetc(fptr);
                *(data + i++) = c;
        }
        //EOF marker at the end of the memory allocation to insure proper handling later
        *(data + (i-1)) = '\0';
}

/*
 * write new data to outputFile;
 */
void outputToFile(char* filename, int size, unsigned char* data) {
	FILE *opt = fopen(filename, "w+");
        fwrite(data, 1, size, opt);
        fclose(opt);
}
