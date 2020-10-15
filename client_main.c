#include <stdio.h>
#include "client_socket.h"


int main(int argc, char *argv[]) {
	client_t client;
	const char *hostname;
	const char *servicename;

	if (argc == 3) {
		hostname = argv[1];

		servicename = argv[2];
	} else {
		printf("Cantidad erronea de argumentos\n");
		return 1;
	}

	client_init(&client, hostname, servicename);

	client_send(&client);

	client_uninit(&client);
	
	return 0;
}