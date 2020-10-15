
#include <stdio.h>

#define MAX 64

//void vigenere_cifrado(char* buffer, char* key);

//void vigenere_descifrado(char* buffer, char* key);

void vigenere_cifrado(char* buffer, char* key){
	int i = 0;
	int j = 0;

	while (buffer[i] != '\0') {
		if(j <= (sizeof(key)/sizeof(char))){
			unsigned char a = ((unsigned int)buffer[i]+(unsigned int)key[j])%256;

			buffer[i] = a;

			i++;

			j++;
		} else{
			j = 0;
		}
	
	}
}

void vigenere_descifrado(char* buffer, char* key){
	int i = 0;
	int j = 0;

	while (buffer[i] != '\0') {
		if(j <= (sizeof(key)/sizeof(char))){
			unsigned char x = ((unsigned int) buffer[i] - (unsigned int)key[j]);
			
			if(buffer[i] < key[j]){
				buffer[i] = (x + 256);
			
			} else {
				buffer[i]  = x;
			}

			i++;

			j++;
		
		} else {
			j = 0;
		}
	}
}

/* int main(void) {
	//char buffer[] = {166, 202, 198, 231, 215, 217, 107, 210, 222, 198, 216, 196, 220, 215};
	unsigned char buffer[] = "Secret message";
	
	char key[] = "SecureKey";

	vigenere_cifrado(buffer, key);

	for(int i = 0; buffer[i] != '\0'; i++){
		printf("%d\n", buffer[i]);

	}

	printf("------------------\n");

	vigenere_descifrado(buffer, key);

	printf("%s\n", buffer);
	
	return 0;
}
*/