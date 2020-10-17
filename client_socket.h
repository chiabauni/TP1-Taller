#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "socket.h"
#include "file_reader.h"
#include "cifrado_vigenere.h"

typedef struct{
	socket_t sockt;
	const char* hostname;
	const char* servicename;
	FILE *fp;
} client_t;

int client_init(client_t *self, const char* hostname, const char* servicename, char* method, void* key);

int client_uninit(client_t *self);

int client_get_input(client_t *self, const char* file_name);

int client_connect(client_t *self);

int client_send(client_t *self);

#endif