#include <stdio.h>
#include "client_socket.h"
#define ARGUMENT_ERROR 1 //codigos de retorno para manejar errores
#define INIT_ERROR 2
#define CONNECT_ERROR 3
#define SEND_ERROR 4
#define UNINIT_ERROR 5
//-------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	client_t client;
	if (argc < 4 || argc > 5) {
		fprintf(stderr, "Error in arguments:./client <server-host>" 
				" <server-port> --method=<method> --key=<key>\n");
		return ARGUMENT_ERROR;
	}
	if (client_init(&client, argv[1], argv[2], &argv[3][9], 
		&argv[4][6], argv[5])) {
		return INIT_ERROR;
	}
	if (client_connect(&client)) {
		return CONNECT_ERROR;
	}
	if (client_send(&client)) {
		return SEND_ERROR;
	}
	if (client_uninit(&client)) {
		return UNINIT_ERROR;
	}
	return 0;
}
