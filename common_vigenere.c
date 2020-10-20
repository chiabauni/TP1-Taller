#include <stdio.h>
#include <string.h>
#include "common_vigenere.h"
#define MAX 64
//-------------------------------------------------------------------------
static void _generate_key(vigenere_t *self, char* buffer,
 						char* key, char* new_key) {
	int j = (self->position % strlen(key));
	for (int i = 0; buffer[i] != '\0'; i++) {
		if (j == strlen(key)) {
			j = 0;
		}
		new_key[i] = key[j];
		j++;
	}
}

void vigenere_init(vigenere_t *self, char* string_key) {
	self->key= string_key;
	self->position = 0;
}

void vigenere_uninit(vigenere_t *self) {}

void vigenere_encode(vigenere_t *self, char* buffer) {
	char new_key[MAX];
	_generate_key(self, buffer, self->key, new_key);
	for (int i = 0; buffer[i] != '\0'; i++) {
		buffer[i] = ((unsigned int)buffer[i] + (unsigned int)new_key[i])%256;
	}
	self->position += strlen(buffer);
}

void vigenere_decode(vigenere_t *self, char* buffer, 
						int bytes_recieved) {
	char new_key[MAX];
	_generate_key(self, buffer, self->key, new_key);
	for (int i = 0; i < bytes_recieved; i++) {
		unsigned char x = ((unsigned int) buffer[i] - (unsigned int)new_key[i]);		
		if (buffer[i] < new_key[i]) {
				buffer[i] = (x + 256);			
		} else {
				buffer[i]  = x;
		}
		buffer[i] = buffer[i]%256; 
	}
	self->position += bytes_recieved;
}
