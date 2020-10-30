#ifndef COMMON_CESAR_H
#define COMMON_CESAR_H
#include <stdio.h>
#include <stdbool.h>
//-------------------------------------------------------------------------
typedef struct {
	char* string_key;
}cesar_t;

/* Recibe un cesar_t y la clave para la encriptacion, inicializa
los atributos correspondientes */
void cesar_init(cesar_t *self, char* string_key);

/* Recibe un cesar_t */
void cesar_uninit(cesar_t *self);

/* Recibe un cesar_t, un buffer con el mensaje a codificar y un 
booleano que indica true si el mensaje de debe codificar y false 
si el mensaje se debe decodificar. Codifica/Decodifica el buffer 
segun corresponda*/
void cesar_encode(cesar_t *self, char* buffer, size_t buffer_size, bool encode);
//-------------------------------------------------------------------------
#endif
