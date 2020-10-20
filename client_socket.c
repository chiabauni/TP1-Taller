#include <stdio.h>
#include "client_socket.h"
#define BUFF_SIZE 64
//-------------------------------------------------------------------------
int client_init(client_t *self, const char* hostname, 
				const char* servicename, char* method, char* key) {
	self->hostname = hostname;
	self->servicename = servicename;
	self->fp = 0;
	socket_t socket;
	if (socket_init(&socket, method, key)) {
		return -1;
	}
	self->sockt = socket;

	return 0;
}

int client_uninit(client_t *self) {
	if (socket_uninit(&self->sockt)) {
		return -1;
	}
	if (self->fp != stdin) {
		if (fclose(self->fp)){
			return -1;
		}
	}
	return 0;
}

int client_get_input(client_t *self, const char* file_name) {
	if (file_name != NULL) {
		self->fp = fopen(file_name, "rb");
		if (self->fp == NULL) {
			return -1;
		}
	} else {
		self->fp = stdin;
	}
	return 0;
}

int client_connect(client_t *self) {
	if (socket_get_addresses(&(self->sockt), 
		self->hostname, self->servicename, 0)) {
		return -1;
	}
	if (socket_connect(&(self->sockt))) {
		return -1;
	}
	return 0;
}

int client_send(client_t *self) {
	char buffer[BUFF_SIZE];
	while (!feof(self->fp)) {
		size_t result = fread(buffer, 1, BUFF_SIZE, self->fp);
		if (ferror(self->fp)) {
			return -1;
		}
		if (socket_send(&(self->sockt), buffer, result)) {
			return -1;
		}
	}
	return 0;
}
