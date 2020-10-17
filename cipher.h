#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>

typedef struct {
	void* key;
	int method;
	char* buffer;
} cipher_t;

int cipher_init(cipher_t *self, char* method, void* key);

int cipher_uninit(cipher_t *self);

void cipher_encode(cipher_t *self, char* buffer);

void cipher_decode(cipher_t *self, char* buffer);

#endif