#include <stdio.h>
#include <string.h>
#include "common_cipher.h"
#define CESAR 0
#define VIGENERE 1
#define RC4 2
//-------------------------------------------------------------------------
int cipher_init(cipher_t *self, char* method, char* key) {
	char cesar[] = "cesar";
	char vigenere[] = "vigenere";
	char rc4[]= "rc4";
	if (method[0] == cesar[0]) {
		self->method = CESAR;
		cesar_init(&(self->cipher_cesar), key);
	} 
	if (method[0] == vigenere[0]) {
		self->method = VIGENERE;
		vigenere_init(&(self->cipher_vigenere), key);
	} 
	if (method[0] == rc4[0]) {
		self->method = RC4;
		rc4_init(&(self->cipher_rc4), key);
	} 
	return 0;
}

int cipher_uninit(cipher_t *self) {
	if (self->method == CESAR) {
		cesar_uninit(&(self->cipher_cesar));
	} 
	if (self->method == VIGENERE) {
		vigenere_uninit(&(self->cipher_vigenere));
	} 
	if (self->method == RC4) {
		rc4_uninit(&(self->cipher_rc4));
	} 
	return 0;
}

void cipher_encode(cipher_t *self, char* buffer) {
	if (self->method == CESAR) {
		cesar_cifrado(&(self->cipher_cesar), buffer);
	} 
	if (self->method == VIGENERE) {
		vigenere_cifrado(&(self->cipher_vigenere), buffer);
	}
	if (self->method == RC4) {
		rc4_cifrado(&(self->cipher_rc4), buffer);
	}
}

void cipher_decode(cipher_t *self, char* buffer, int bytes_recieved) {
	if (self->method == CESAR) {
		cesar_descifrado(&(self->cipher_cesar), buffer, bytes_recieved);
	} 
	if (self->method == VIGENERE) {
		vigenere_descifrado(&(self->cipher_vigenere), buffer, bytes_recieved);
	}
	if (self->method == RC4) {
		rc4_descifrado(&(self->cipher_rc4), buffer, bytes_recieved);
	}
}