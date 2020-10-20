#ifndef COMMON_VIGENERE_H
#define COMMON_VIGENERE_H
#include <stdio.h>
//-------------------------------------------------------------------------
typedef struct {
	char* key;
	int position;
}vigenere_t;

/* Recibe un vigenere_t y la clave para la encriptacion, inicializa
los atributos correspondientes */
void vigenere_init(vigenere_t *self, char* string_key);

/* Recibe un vigenere_t */
void vigenere_uninit(vigenere_t *self);

/* Recibe un vigenere_t y un buffer con el mensaje a codificar. 
Codifica el buffer */
void vigenere_encode(vigenere_t *self, char* buffer);

/* Recibe un vigenere_t, un buffer con el mensaje a codificar 
y la cantidad de bytes recibidos. Decodifica el buffer */
void vigenere_decode(vigenere_t *self, char* buffer, 
						int bytes_recieved);
//-------------------------------------------------------------------------
#endif
