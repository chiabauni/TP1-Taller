#include <stdio.h>
#include "server_socket.h"
//#include "client_socket.h"


int server_init(server_t *self, const char* servicename) {
	self->hostname = 0;
	self->servicename = servicename;

	socket_t socket, peer;
	socket_init(&socket);
	socket_init(&peer);

	self->sockt = socket;
	self->peer = peer;

	return 0;
}

int server_uninit(server_t *self) {
	if (socket_uninit(&self->sockt)) {
		return -1;
	} 
	if (socket_uninit(&self->peer)) {
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

/*nt server_receive(server_t *self, char *buffer, size_t buffer_size) {
	if (socket_receive(&(self->peer), buffer, buffersize)) {
		return -1;
	}
	return 0;
}*/


