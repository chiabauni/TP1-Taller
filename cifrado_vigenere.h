#ifndef CIFRADO_VIGENERE_H
#define CIFRADO_VIGENERE_H

#include <stdio.h>

void vigenere_cifrado(unsigned char* buffer, char* key);

void vigenere_descifrado(unsigned char* buffer, char* key);

#endif