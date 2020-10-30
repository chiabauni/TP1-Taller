#ifndef COMMON_VIGENERE_H
#define COMMON_VIGENERE_H
#include <stdio.h>
#include <stdbool.h>
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

/* Recibe un vigenere_t, un buffer con el mensaje a codificar y un 
booleano que indica true si el mensaje de debe codificar y false 
si el mensaje se debe decodificar. Codifica/Decodifica el buffer 
segun corresponda*/ 
void vigenere_encode(vigenere_t *self, char* buffer, 
					size_t buffer_size, bool encode);
//-------------------------------------------------------------------------
#endif
