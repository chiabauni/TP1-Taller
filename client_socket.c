#include <stdio.h>
#include "client_socket.h"

#define BUFF_SIZE 64

int client_init(client_t *self, const char* hostname, const char* servicename) {
	self->hostname = hostname;
	self->servicename = servicename;

	socket_t socket;

	socket_init(&socket);

	self->sockt = socket;

	return 0;
}

int client_uninit(client_t *self) {
	if(socket_uninit(&self->sockt)){
		return -1;
	}
	if (self->fp != stdin) {
		fclose(self->fp);//agergar casos en el que fclose devuelve error
	}
	return 0;
}

int client_connect(client_t *self){
	if(socket_get_addresses(&(self->sockt), self->hostname, self->servicename, 0)){
		return -1;
	}

	if (socket_connect(&(self->sockt))){
		return -1;
	}
}

int client_get_input(client_t *self, const char* file_name){
	if(file_name != NULL) {
		self->fp = fopen(file_name, "rb"); //agergar casos en el que fopen devuelve error
	} else {
		self->fp = stdin;
	}
	return 0;
}

int client_send(client_t *self) {

	char buffer[BUFF_SIZE];
	size_t result;

	while (!feof(self->fp)) {
		result = fread(buffer, 1, BUFF_SIZE, self->fp);//agergar casos en el que fread devuelve error
		//callback(buffer, result, callback_ctx);
	}

	if (socket_send(&(self->sockt), buffer, result)) {
		return -1;
	}
	return 0;
}
