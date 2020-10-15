
#include <stdio.h>

#define MAX 64

//void cesar_descifrado(char* buffer, unsigned int key);
//void cesar_cifrado(char* buffer, unsigned int key);

void cesar_cifrado(char* buffer, unsigned int key){
	for (int i = 0; buffer[i] != '\0'; i++){
		
		unsigned char a =  ((unsigned int)buffer[i] + key)%256;
		
		buffer[i] = a;
	}
}

void cesar_descifrado(char* buffer, unsigned int key){
	for (int i = 0; buffer[i] != '\0'; i++){
		
		if(buffer[i] < key){
			int x = ((unsigned int)buffer[i] - key);
			
			buffer[i] = (unsigned char) (x + 256);
			
		} else {
			buffer[i]  = (unsigned char)((unsigned int)buffer[i] - key);
			
		}

	}
}

/*int main(void) {
	//unsigned char buffer[] = {254, 5, 2, 247, 16, 241, 17, 182, 19};
	unsigned char buffer[] = "holaz[{ }";
	
	unsigned int key = 150;

	cesar_cifrado(buffer, key);
	
	for(int i = 0; buffer[i] != '\0'; i++){
		printf("%d\n", buffer[i]);

	}
	
	printf("---------------------\n");
	
	cesar_descifrado(buffer, key);

	printf("%s\n", buffer);
	
	return 0;
}
*/