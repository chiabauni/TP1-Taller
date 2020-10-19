#ifndef COMMON_CIPHER_H
#define COMMON_CIPHER_H

#include <stdio.h>
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
//-------------------------------------------------------------------------
typedef struct {
	int method;
	cesar_t cipher_cesar;
	vigenere_t cipher_vigenere;
	rc4_t cipher_rc4;
} cipher_t;

int cipher_init(cipher_t *self, char* method, char* key);

int cipher_uninit(cipher_t *self);

void cipher_encode(cipher_t *self, char* buffer);

void cipher_decode(cipher_t *self, char* buffer, int bytes_recieved);
//-------------------------------------------------------------------------
#endif