#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "socket.h"

typedef struct{
	socket_t sockt;
	socket_t peer;
	const char* hostname;
	const char* servicename;
} server_t;

int server_init(server_t *self, const char* servicename);

int server_uninit(server_t *self);

int server_connect(server_t *self);

//int server_receive(server_t *self);

#endif