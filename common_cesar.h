#ifndef COMMON_CESAR_H
#define COMMON_CESAR_H
#include <stdio.h>
//-------------------------------------------------------------------------
typedef struct {
	char* string_key;
}cesar_t;

/* Recibe un cesar_t y la clave para la encriptacion, inicializa
los atributos correspondientes */
void cesar_init(cesar_t *self, char* string_key);

/* Recibe un cesar_t */
void cesar_uninit(cesar_t *self);

/* Recibe un cesar_t y un buffer con el mensaje a codificar. 
Codifica el buffer */
void cesar_encode(cesar_t *self, char* buffer);

/* Recibe un cesar_t, un buffer con el mensaje a codificar 
y la cantidad de bytes recibidos. Decodifica el buffer */
void cesar_decode(cesar_t *self, char* buffer, 
					int bytes_recieved);
//-------------------------------------------------------------------------
#endif
