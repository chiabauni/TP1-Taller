#ifndef CIFRADO_RC4_H
#define CIFRADO_RC4_H

#include <stdio.h>

void swap(unsigned char* x, unsigned char* y);
int KSA(unsigned char* key, unsigned char* S);
int PRGA(unsigned char* S, char* buffer, char* result);

#endif