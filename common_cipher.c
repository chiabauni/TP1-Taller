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

void cipher_encode(cipher_t *self, char* buffer, size_t buffer_size) {
	if (self->method == CESAR) {
		cesar_encode(&(self->cipher_cesar), buffer, buffer_size);
	} 
	if (self->method == VIGENERE) {
		vigenere_encode(&(self->cipher_vigenere), buffer, buffer_size);
	}
	if (self->method == RC4) {
		rc4_encode(&(self->cipher_rc4), buffer, buffer_size);
	}
}

void cipher_decode(cipher_t *self, char* buffer, int bytes_recieved) {
	if (self->method == CESAR) {
		cesar_decode(&(self->cipher_cesar), buffer, bytes_recieved);
	} 
	if (self->method == VIGENERE) {
		vigenere_decode(&(self->cipher_vigenere), buffer, bytes_recieved);
	}
	if (self->method == RC4) {
		rc4_decode(&(self->cipher_rc4), buffer, bytes_recieved);
	}
}
