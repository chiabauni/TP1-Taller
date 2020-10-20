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

/* Recibe un rc4_t y la clave para la encriptacion, inicializa
los atributos correspondientes */
void rc4_init(rc4_t *self, char* key);

/* Recibe un rc4_t */
void rc4_uninit(rc4_t *self);

/* Recibe un rc4_t y un buffer con el mensaje a codificar. 
Codifica el buffer */
void rc4_encode(rc4_t *self, char* buffer);

/* Recibe un rc4_t, un buffer con el mensaje a codificar 
y la cantidad de bytes recibidos. Decodifica el buffer */
void rc4_decode(rc4_t *self, char* buffer, int bytes_recieved);
//-------------------------------------------------------------------------
#endif
