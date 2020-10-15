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
	file_reader_t fr;
} client_t;

int client_init(client_t *self,const char *hostname, const char *servicename);

int client_uninit(client_t *self);

int client_send(client_t *self);

static void _send_buffer(char *buffer, 
	                    size_t buffer_size,
	                    void *callback_context);

#endif