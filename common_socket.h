#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H
#include <stdio.h>
#include <stdbool.h>
#include "common_cipher.h"
//-------------------------------------------------------------------------
typedef struct{
	int fd;
	struct addrinfo* results_getaddr;
	cipher_t cipher;
} socket_t;

int socket_init(socket_t *self, char* method, char* key);

int socket_uninit(socket_t *self);

int socket_get_addresses(socket_t *self, const char *host, 
						const char *service, bool is_server);

int socket_listen(socket_t *self);

int socket_bind(socket_t *self);

int socket_accept(socket_t *listener, socket_t *peer);

int socket_connect(socket_t *self);

int socket_send(socket_t *self, unsigned char* buffer, size_t buffer_size);

int socket_receive(socket_t *self, unsigned char* buffer, size_t buffer_size);

int socket_close(socket_t *self);
//-------------------------------------------------------------------------
#endif