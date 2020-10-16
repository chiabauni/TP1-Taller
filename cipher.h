#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>

typedef struct {
	const char* key;
	const char* method;
	char* buffer;
} cipher_t;

int cipher_init(cifrado_t *self, const char* method, const char* key, char* buffer);

int cipher_uninit(cifrado_t *self);

int cipher_encode(cifrado_t *self);

int cifrado_decode(cifrado_t *self);

#endif