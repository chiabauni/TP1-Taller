#include <stdio.h>
#include "client_socket.h"
//-------------------------------------------------------------------------
/* Adaptador entre la interfaz del client_send y la interfaz del callback */
static void _send_encrypted_buffer(char *buffer, 
	                    size_t buffer_size,
	                    void *callback_ctx) {
	socket_t *socket = callback_ctx;
	socket_send(socket, buffer, buffer_size);
}

int client_init(client_t *self, const char* hostname, 
				const char* servicename, char* method, 
				char* key, const char* file_name){
	self->hostname = hostname;
	self->servicename = servicename;
	socket_t socket;
	if (socket_init(&socket)) {
		return -1;
	}
	self->sockt = socket;
	if (file_encryptor_init(&(self->file_encryptor), 1, 
		method, key, file_name)) {
		return -1;
	}	
	return 0;
}

int client_uninit(client_t *self) {
	if (socket_uninit(&self->sockt)) {
		return -1;
	}
	if (file_encryptor_uninit(&(self->file_encryptor), 1)) {
		return -1;
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
	if (file_encryptor_encrypt(&(self->file_encryptor), 
		_send_encrypted_buffer, &(self->sockt))) {
		return -1;
	}
	return 0;
}
