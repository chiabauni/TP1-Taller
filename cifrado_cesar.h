#ifndef CIFRADO_CESAR_H
#define CIFRADO_CESAR_H

#include <stdio.h>

void cesar_cifrado(unsigned char* buffer, unsigned char* string_key);

void cesar_descifrado(unsigned char* buffer, unsigned char* string_key);

#endif