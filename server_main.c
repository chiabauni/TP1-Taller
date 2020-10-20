#include <stdio.h>
#include "server_socket.h"
#define ARGUMENT_ERROR 1
#define INIT_ERROR 2
#define CONNECT_ERROR 3
#define RECEIVE_ERROR 4
#define UNINIT_ERROR 2
//-------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Error in arguments: ./server <server-port>"
            " --method=<method> --key=<key>\n");
    return ARGUMENT_ERROR;
  }
  server_t server;
  if (server_init(&server, argv[1], &argv[2][9], &argv[3][6])) {
    return INIT_ERROR;
  }
  if (server_connect(&server)) {
    return CONNECT_ERROR;
  }
  if (server_receive(&server)) {
    return RECEIVE_ERROR;
  }
  if (server_uninit(&server)) {
    return UNINIT_ERROR;
  }
  return 0;
}
