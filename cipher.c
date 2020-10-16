#include <stdio.h>

#include "cipher.h"
#include "cifrado_cesar.h"
#include "cifrado_vigenere.h"
#include "cifrado_RC4.h"

int cipher_init(cifrado_t *self, const char* method, const char* key, char* buffer) {
	self->method = method;
	self->key = key;
	self->buffer = buffer;
	return 0;
}

int cipher_uninit(cifrado_t *self) {
	self->method = -1;
	self->key = -1;
	self->buffer = -1;
	return 0;
}

int cipher_encode(cifrado_t *self) {
	if (&(self->method) == "cesar") {
		cesar_cifrado(&(self->buffer), &(self->key));
	} 
	if (&(self->method) == "vigenere") {
		vigenere_cifrado(&(self->buffer), &(self->key))
	}
	if (&(self->method) == "rc4") {
		rc4_cifrado(&(self->buffer), &(self->key))
	}
}

int cifrado_decode(cifrado_t *self) {
	if (&(self->method) == "cesar") {
		cesar_descifrado(&(self->buffer), &(self->key));
	} 
	if (&(self->method) == "vigenere") {
		vigenere_descifrado(&(self->buffer), &(self->key))
	}
	if (&(self->method) == "rc4") {
		rc4_descifrado(&(self->buffer), &(self->key))
	}
}