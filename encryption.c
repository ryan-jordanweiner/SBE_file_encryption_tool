#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MULTIPLIER (463)
#define MODULUS (256)
extern void encrypt_data(unsigned char* unencrypted_data, int size) {
	
	/*implement encryption algorithm on unencrypted data here*/
	/*caeser shift +7 used here*/
	
	char password[81];
	
	printf("Input password for the file:\n");
	

	//take password input
	int index = 0;
	char ch;
	while ((ch = getchar()) != '\n') {
		password[index++] = ch;
	}	
	password[index] = '\0';

	long long hashNum = 0;
	
	for (int index = 0; password[index] != '\0'; index++) {
		hashNum += (MULTIPLIER*password[index]);
	}
	
	hashNum %= MODULUS;
	unsigned char tempChar;
	printf("hashNum: %lld\n", hashNum);
	for (int i = 0; i < size; i++) {
		tempChar = (*(unencrypted_data + i));
		printf("original character: %d  ", tempChar);

		tempChar *= hashNum;
		tempChar %= MODULUS;

		printf("encrypted char: %d\n", tempChar);

		(*(unencrypted_data + i)) = tempChar;
	}

	return ;
}

extern void encrypt_chunked(unsigned char* data, int size) {
	unsigned char chunk[4];
	long chunkSum = 0;
	printf("%d\n", size);

	char password[81];

        printf("Input password for the file:\n");


        //take password input
        int index = 0;
        char ch;
        while ((ch = getchar()) != '\n') {
                password[index++] = ch;
        }
        password[index] = '\0';

        long long hashNum = 0;

        for (int index = 0; password[index] != '\0'; index++) {
                hashNum += (MULTIPLIER*password[index]);
        }

        hashNum %= MODULUS;


	for (int i = 0; i < size/4; i++){
		chunkSum = 0;
		for (int d = 0; d < 4; d++){
			printf("%02x ", data[i*4+d]);
			chunk[d] = data[i*4+d];	
			chunkSum += pow(10, 2*d)*((int) chunk[d]);	
		}

		printf("encrypted chunk = %ld\n", (chunkSum*hashNum)%654654);
	
		printf("    chunk data: %ld    ", chunkSum);
		printf("\n");
	}


}

extern void decrypt_data(unsigned char* encrypted_data, int size) {
	/*
	 * implement decryption algorithm here
	 * reverse caeser shift used here
	 */

	char password[81];

        printf("Input password for the file:\n");


        //take password input
        int index = 0;
        char ch;
        while ((ch = getchar()) != '\n') {
                password[index++] = ch;
        }
        password[index] = '\0';

        long long hashNum = 0;

        for (int index = 0; password[index] != '\0'; index++) {
                hashNum += (MULTIPLIER*password[index]);
        }
	hashNum %= MODULUS;
	
	double temp;
	double mult;
	for (int i = 0; i < size; i++) {
		temp = .4;
		mult = 0;
		while (!(ceil(temp) == floor(temp))) {
			temp = (*(encrypted_data + i));
			temp = (((temp/ MODULUS)+(mult++))*MODULUS)/hashNum;
		}
		(*(encrypted_data + i)) = (unsigned char) temp;
		printf("decrypted character: %d\n", (unsigned char) temp);
	}
	
	return ;
}
