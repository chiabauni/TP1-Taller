#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdbool.h>
//#include <stdint.h>
//#include <unistd.h>

typedef struct{
	int fd;
	struct addrinfo* results_getaddr;
} socket_t;

int socket_init(socket_t *self);

int socket_uninit(socket_t *self);

int socket_get_addresses(socket_t *self, const char *host, const char *service, bool is_server);

int socket_listen(socket_t *self);

int socket_bind(socket_t *self);

int socket_accept(socket_t *listener, socket_t *peer);

int socket_connect(socket_t *self);

int socket_send(socket_t *self, char *buffer, size_t buffer_size);

int socket_receive(socket_t *self, char *buffer, size_t buffer_size);

int socket_close(socket_t *self);

#endif