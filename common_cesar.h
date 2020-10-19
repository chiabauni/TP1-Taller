#ifndef COMMON_CESAR_H
#define COMMON_CESAR_H
#include <stdio.h>
//-------------------------------------------------------------------------
typedef struct {
	unsigned char* string_key;
}cesar_t;

void cesar_init(cesar_t *self, unsigned char* string_key);

void cesar_uninit(cesar_t *self);

void cesar_cifrado(cesar_t *self, unsigned char* buffer);

void cesar_descifrado(cesar_t *self, unsigned char* buffer, 
					int bytes_recieved);
//-------------------------------------------------------------------------
#endif