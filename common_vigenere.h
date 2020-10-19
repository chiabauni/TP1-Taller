#ifndef COMMON_VIGENERE_H
#define COMMON_VIGENERE_H
#include <stdio.h>
//-------------------------------------------------------------------------
typedef struct {
	unsigned char* key;
	int position;
}vigenere_t;

void vigenere_init(vigenere_t *self, unsigned char* string_key);

void vigenere_uninit(vigenere_t *self);

void vigenere_cifrado(vigenere_t *self, unsigned char* buffer);

void vigenere_descifrado(vigenere_t *self, unsigned char* buffer, 
						int bytes_recieved);
//-------------------------------------------------------------------------
#endif