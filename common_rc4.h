#ifndef COMMON_RC4_H
#define COMMON_RC4_H
#include <stdio.h>
#define MAX_SIZE 256
//-------------------------------------------------------------------------
typedef struct {
	int i;
	int j;
	int n;
	char* key;
	unsigned char S[MAX_SIZE];
} rc4_t;

void rc4_init(rc4_t *self, char* key);

void rc4_uninit(rc4_t *self);

void rc4_cifrado(rc4_t *self, char* buffer);

void rc4_descifrado(rc4_t *self, char* buffer, int bytes_recieved);
//-------------------------------------------------------------------------
#endif