#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common_rc4.h"
#define MAX 255
//-------------------------------------------------------------------------
static void _swap(unsigned char* x, unsigned char* y) {
    unsigned char temp = *x;
    *x = *y;
    *y = temp;
}

static void _KSA(rc4_t *self, char* key, unsigned char* S) {
    int key_length = strlen(key);
    for (int k = 0; k < 256; k++) {
        S[k] = k;
    }
    int m = 0;
    for (int k = 0; k < 256; k++) {
        m = (m + S[k] + key[k % key_length]) & MAX;
        _swap(&S[k], &S[m]);
    }
}

static void _PRGA(rc4_t *self, unsigned char* S, 
                char* buffer, int bytes_recieved) {
    for (int k = 0; k < bytes_recieved; k++) {
        self->i = (self->i + 1) & MAX;    
        self->j = (self->j + S[self->i]) & MAX;        
        _swap(&S[self->i], &S[self->j]);
        int a = S[(S[self->i] + S[self->j]) & MAX];
        buffer[k] = buffer[k] ^ a;
        buffer[bytes_recieved]='\0';
    }
    buffer[bytes_recieved]='\0';
}

void rc4_init(rc4_t *self, char* key){
    self->key = key;
    self->i = 0;
    self->j = 0;
    self->n = 0;
}

void rc4_uninit(rc4_t *self) {
    self->i = -1;
    self->j = -1;
    self->n = -1;
}

void rc4_encode(rc4_t *self, char* buffer, size_t buffer_size) {    
    if (self->n == 0) {
        _KSA(self,self->key, self->S);
        self->n++;
    }
    _PRGA(self, self->S, buffer, (int)buffer_size);
}

void rc4_decode(rc4_t *self, char* buffer, int bytes_recieved) {    
    if (self->n == 0) {
        _KSA(self, self->key, self->S);
        self->n++;
    }
    _PRGA(self, self->S, buffer, bytes_recieved);
}
