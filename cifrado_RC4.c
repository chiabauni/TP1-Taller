#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 256

void swap(unsigned char* x, unsigned char* y);
int KSA(unsigned char* key, unsigned char* S);
int PRGA(unsigned char* S, char* buffer, char* result);

void swap(unsigned char* x, unsigned char* y) {
    unsigned char temp = *x;
    *x = *y;
    *y = temp;
}

int KSA(unsigned char* key, unsigned char* S) {
    int key_length = strlen(key);

    int j = 0;

    for (int i = 0; i < MAX_SIZE; i++)
        S[i] = i;
 
    for (int i = j = 0; i < MAX_SIZE; i++) {
        j = (j + S[i] + key[i % key_length]) % MAX_SIZE;
        
        swap(&S[i], &S[j]);
    }
    return 0;
}
 

int PRGA(unsigned char* S, char* buffer, char* result) {
    int i = 0;

    int j = 0;
    
    for(size_t k = 0; k < strlen(buffer); k++) {
        i = (i + 1) % MAX_SIZE;
    
        j = (j + S[i]) % MAX_SIZE;
        
        swap(&S[i], &S[j]);

        int a = S[(S[i] + S[j]) % MAX_SIZE];

        result[k] = buffer[k] ^ a;

    }
    return 0;
}

int main() {
    unsigned char key[]= "queso";

    unsigned char buffer[] = "Pan";

    unsigned char *result= malloc(sizeof(int) * strlen(buffer)); 

    unsigned char S[MAX_SIZE];
    
    KSA(key, S);

    PRGA(S, buffer, result);

    for(size_t i = 0; i < strlen(buffer); i++){
        printf("%02X\n",buffer[i]);
    }

    free(result);

    return 0;
}