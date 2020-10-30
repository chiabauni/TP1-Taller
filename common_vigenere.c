#include <stdio.h>
#include <string.h>
#include "common_vigenere.h"
#define MAX 64
//-------------------------------------------------------------------------
static void _generate_key(vigenere_t *self, char* buffer,
 						char* key, char* new_key, int buffer_size) {
	int j = (self->position % strlen(key));
	for (int i = 0; i < buffer_size; i++) {
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

void vigenere_encode(vigenere_t *self, char* buffer, 
					size_t buffer_size, bool encode) {
	char new_key[MAX];
	_generate_key(self, buffer, self->key, new_key, (int)buffer_size);
	for (int i = 0; i < buffer_size; i++) {
		unsigned char x = ((unsigned int)buffer[i]-(unsigned int)new_key[i]);
		if (encode) {
			buffer[i] = ((unsigned int)buffer[i]+(unsigned int)new_key[i])%256;
		} else if (buffer[i] < new_key[i]) {
				buffer[i] = (x + 256) % 256;			
		} else {
				buffer[i]  = x % 256;
		}
	}
	self->position += buffer_size;
}
