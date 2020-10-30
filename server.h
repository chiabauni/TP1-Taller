#ifndef SERVER_H
#define SERVER_H
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "common_socket.h"
#include "common_file_encryptor.h"
/* Cambio el nombre del archivo de server_socket.h a server.h */
//-------------------------------------------------------------------------
typedef struct{
	socket_t sockt;
	socket_t peer;
	const char* hostname;
	const char* servicename;
	file_encryptor_t file_encryptor;
} server_t;

/* Recibe un server_t, el port, el nombre del metodo 
con el que se va a encriptar y la clave para encriptar.
Inicializa el server pasado por parametro con sus respectivos 
atributos. Devuelve -1 en caso de error, sino devuelve 0.  */
int server_init(server_t *self, const char* servicename, 
				char* method, void* key);

/* Recibe un server_t y destruye el servidor liberando los recursos 
utilizados, si no hay errores devuelve 0 sino devuelve -1   */
int server_uninit(server_t *self);

/* Recibe un server_t establece la conexion del servidor, el servidor 
queda a escucha de nuevas conexiones y acepta la primera conexion entrante. 
Devuelve -1 en caso de error, sino devuelve 0. */
int server_connect(server_t *self);

/* Recibe un server_t y recibe un mensaje a traves de la conexion generada 
anteriormente. Devuelve -1 en caso de error, sino devuelve 0. */
int server_receive(server_t *self);
//-------------------------------------------------------------------------
#endif
