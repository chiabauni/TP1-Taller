#ifndef COMMON_FILE_ENCRYPTOR_H
#define COMMON_FILE_ENCRYPTOR_H
#include <stdio.h>
#include <stdbool.h>
#include "common_cipher.h"
#include "common_cipher.h"
//-------------------------------------------------------------------------
typedef struct {
	FILE *fp;
	cipher_t cipher;
}file_encryptor_t;

/* Defino un tipo llamado file_encryptor_callback_t que recibe como 
parametros un buffer y su longitud en bytes y un puntero generico 
callback_context*/
typedef void (*file_encryptor_callback_t)(char *buffer, 
	                                   size_t buffer_size,
	                                   void *callback_ctx);

/* Recibe un file_encryptor_t, un booleano que es true si es cliente y 
false si es server, el nombre del metodo con el que se va a encriptar, 
la clave para encriptar y un nombre de archivo(si es por stdin o el 
server recibe NULL). Se inicializan los atributos correspondientes. 
Devuelve -1 en caso de error sino devuelve 0. */
int file_encryptor_init(file_encryptor_t *self, bool is_client, 
						char* method, char* key, const char* file_name);

/* Recibe un file_encryptor_t, un booleano que es true si es cliente y 
false si es server. Se destruye el file_encryptor liberando los recursos 
utilizados,devuelve -1 en caso de error sino devuelve 0. */
int file_encryptor_uninit(file_encryptor_t *self, bool is_client);

/* Recibe un file_encryptor_t,un callback de tipo file_encryptor_callback_t
y su respectivo contexto. Lee el texto de a buffers de 64 bytes, 
encripta cada buffer y se hace un callback para que la funcion send de 
common_socket a traves de un adaptador reciba el buffer encriptado. 
Devuelve -1 en caso de error sino devuelve 0.*/
int file_encryptor_encrypt(file_encryptor_t *self, 
							file_encryptor_callback_t callback,
	                    	void *callback_ctx);

/* Recibe un file_encryptor_t, un buffer y longitud de bytes a desencriptar, 
se desencripta y se imprime el buffer. Devuelve -1 en caso de error 
sino devuelve 0. */
int file_encryptor_decrypt(file_encryptor_t *self, 
							char* buffer, size_t bytes_received);
//-------------------------------------------------------------------------
#endif
