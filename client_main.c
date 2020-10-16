#include <stdio.h>
#include "client_socket.h"


int main(int argc, char *argv[]) {
	client_t client;
	const char *method;
	const char *key;

	//client_set_arguments(&client, argc, argv, method, key);

	client_init(&client, argv[1], argv[2]);

	client_get_input(&client, argv[5]);

	client_connect(&client);

	client_send(&client);

	client_uninit(&client);
	
	return 0;
}