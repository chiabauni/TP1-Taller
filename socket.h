#ifndef SOCKET_H
#define SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

typedef struct{
	int s;
} socket_t;

int socket_init(socket_t *self);

int socket_uninit(socket_t *self);

int socket_bind_and_listen(socket_t *self, const char *host, const char *service);

int socket_accept(socket_t *listener, socket_t *peer);

int socket_connect(socket_t *self, const char *host, const char *service);

ssize_t socket_send(socket_t *self, char *buffer, size_t lenght);

ssize_t socket_receive(socket_t *self, char *buffer, size_t lenght);

void socket_close(socket_t *self);

int socket_status_error(socket_t *self, int status);

#endif