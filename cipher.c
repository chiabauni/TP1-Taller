#include <stdio.h>

#include "cipher.h"
#include "cifrado_cesar.h"
#include "cifrado_vigenere.h"
#include "cifrado_RC4.h"

#define CESAR 0
#define VIGENERE 1
#define RC4 2


int cipher_init(cipher_t *self, char* method, void* key) {
	char cesar[] = "cesar";
	char vigenere[] = "vigenere";
	char rc4[]= "rc4";
	
	if (method[0] == cesar[0]) {
		self->method = CESAR;
	} 
	if (method[0] == vigenere[0]) {
		self->method = VIGENERE;
	} 
	if (method[0] == rc4[0]) {
		self->method = RC4;
	} 

	self->key = key;
	return 0;
}

int cipher_uninit(cipher_t *self) {

	return 0;
}

void cipher_encode(cipher_t *self, char* buffer) {
	self->buffer = buffer;
	if (self->method == 0) {
		cesar_cifrado(self->buffer, self->key);
	} 
	if (self->method == 1) {
		vigenere_cifrado(self->buffer, self->key);
	}
	if (self->method == 2) {
		rc4_cifrado(self->buffer, self->key);
	}
}

void cipher_decode(cipher_t *self, char* buffer) {
	self->buffer = buffer;
	if (self->method == 0) {
		cesar_descifrado(self->buffer, self->key);
	} 
	if (self->method == 1) {
		vigenere_descifrado(self->buffer, self->key);
	}
	if (self->method == 2) {
		rc4_cifrado(self->buffer, self->key);
	}
}

/*int main(){
	cipher_t cipher;
	char method[] = "cesar";
	char key[] = {5};
	char buffer[] = "Pan";

	cipher_init(&cipher, method, key);
	cipher_encode(&cipher, buffer);
	for(int i = 0; buffer[i] != '\0'; i++){
		printf("%x\n", buffer[i]);

	}
	cipher_uninit(&cipher);
}*/