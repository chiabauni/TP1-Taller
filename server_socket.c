#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "server_socket.h"
#define BUFF_SIZE 64
//-------------------------------------------------------------------------
int server_init(server_t *self, const char* servicename, 
				char* method, void* key) {
	self->hostname = 0;
	self->servicename = servicename;
	socket_t socket;
	socket_t peer;
	if (socket_init(&socket)) {
		return -1;
	}
	if (socket_init(&peer)) {
		return -1;
	}
	self->sockt = socket;
	self->peer = peer;
	if (file_encryptor_init(&(self->file_encryptor), 0, 
		method, key, NULL)) {
		return -1;
	}	
	return 0;
}

int server_uninit(server_t *self) {
	if (socket_uninit(&self->sockt)) {
		return -1;
	} 
	if (socket_uninit(&self->peer)) {
		return -1;
	}
	if (file_encryptor_uninit(&(self->file_encryptor), 0)) {
		return -1;
	}
	return 0;
}

int server_connect(server_t*self) {
	if (socket_get_addresses(&(self->sockt), 0, self->servicename, 1)) {
		return -1;
	}
	if (socket_bind(&self->sockt)) {
		return -1;
	}
	if (socket_listen(&self->sockt)) {
		return -1;
	}
	if (socket_accept(&(self->sockt), &(self->peer))) {
		return -1;
	}
	return 0;
}

int server_receive(server_t *self) {
	char buffer[BUFF_SIZE];
	int status = 1;
	do {
		status = socket_receive(&(self->peer), buffer, BUFF_SIZE);
		if (file_encryptor_decrypt(&(self->file_encryptor), 
			buffer, status)) {
			return -1;
		}
	} while (status > 0);
	if (status == -1) {
		fprintf(stderr, "Error in server_receive:%s\n", strerror(status));
		return -1;
	}
	return 0;
}
