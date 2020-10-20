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

/* Recibe un cipher_t, el nombre del metodo con el que se va a encriptar
 y la clave para encriptar. Se inicializa el metodo de encriptacion segun
 cual haya sido elegido, si no hay errores devuelve 0 sino devuelve -1 */
int cipher_init(cipher_t *self, char* method, char* key);

/* Recibe un cipher_t y libera los recursos utilizados. Si no hay errores
 devuelve 0 sino devuelve -1 */
int cipher_uninit(cipher_t *self);

/* Recibe un cipher_t y un buffer y elige segun el metodo seleccionado
por el usuario la funcion de cifrado a utilizar, enviandole el buffer. */
void cipher_encode(cipher_t *self, char* buffer, size_t buffer_size);

/* Recibe un cipher_t , un buffer y su longitud en bytes. Elige segun
el metodo seleccionado por el usuario la funcion de descifrado a utilizar,
enviandole el buffer. */
void cipher_decode(cipher_t *self, char* buffer, int bytes_recieved);
//-------------------------------------------------------------------------
#endif
