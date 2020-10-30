#include <stdio.h>
#include <string.h>
#include "common_cesar.h"
//-------------------------------------------------------------------------
void cesar_init(cesar_t *self, char* string_key){
	self->string_key = string_key;
}

void cesar_uninit(cesar_t *self){}

void cesar_encode(cesar_t *self, char* buffer, 
					size_t buffer_size, bool encode) {
	unsigned int key = (unsigned int)(self->string_key[0]-'0');
	for (int i = 0; i < buffer_size; i++) {		
		if (encode) {
			buffer[i] =  ((unsigned int)buffer[i] + key)%256;
		} else if (buffer[i] < key) {
			int x = ((unsigned int)buffer[i] - key);			
			buffer[i] = (unsigned char) (x + 256);			
		} else {
			buffer[i]  = (unsigned char)((unsigned int)buffer[i] - key);			
		}
	}
}
