#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "common_socket.h"
#include "common_file_encryptor.h"
//-------------------------------------------------------------------------
typedef struct{
	socket_t sockt;
	const char* hostname;
	const char* servicename;
	file_encryptor_t file_encryptor;
} client_t;

/* Recibe un client_t, el host, el port, el nombre del metodo 
con el que se va a encriptar y la clave para encriptar. 
Inicializa el client_t, si no hay errores devuelve 0 sino devuelve -1 */
int client_init(client_t *self, const char* hostname, 
				const char* servicename, char* method, 
				char* key, const char* file_name);

/* Recibe un client_t y destruye el cliente liberando los recursos 
utilizados, si no hay errores devuelve 0 sino devuelve -1  */
int client_uninit(client_t *self);

/* Recibe un client_t y un nombre de archivo(si es por stdin recibe NULL), 
se estabalece el puntero fp en el puntero devuelto por fopen
(si es por stdin se establece el puntero en stdin). 
Si no hay errores devuelve 0 sino devuelve -1 */
/*int client_get_input(client_t *self, const char* file_name);*/

/* Recibe un client_t intenta conectar el cliente con el servidor, 
si falla devuelve -1 sino devuelve 0. */
int client_connect(client_t *self);

/* Recibe un client_t y mientras no se haya terminado de leer el texto 
envia buffers de 64 bytes al servidor. 
Si no hay errores devuelve 0 sino devuelve -1 */
int client_send(client_t *self);
//-------------------------------------------------------------------------
#endif
