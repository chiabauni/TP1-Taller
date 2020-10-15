#include <stdio.h>
#include "client_socket.h"

int client_init(client_t *self,const char *hostname, const char *servicename) {
	//const char *hostname = "localhost";

	//const char *servicename = "7777";

	file_reader_init(&self->fr, NULL);

	socket_init(&self->sockt);

	socket_connect(&self->sockt, hostname, servicename);

	return 0;
}

int client_uninit(client_t *self) {
	socket_uninit(&self->sockt);
	
	file_reader_uninit(&self->fr);

	return 0;
}

int client_send(client_t *self) {

	file_reader_for_each_buffer(&self->fr, _send_buffer, &self->sockt);

	return 0;
}

static void _send_buffer(char *buffer, 
	                    size_t buffer_size,
	                    void *callback_context) {
	socket_t *socket = callback_context;

	vigenere_cifrado(buffer, "SecureKey");

	socket_send(socket, buffer, buffer_size);
}