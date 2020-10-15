#include <stdio.h>
#include "socket.h"
#include "client_socket.h"


#define BUFF_SIZE 64

int main(int argc, char *argv[]) {
  socket_t server;

  char buffer[BUFF_SIZE];
  
  const char *hostname = "localhost";

  const char *servicename = "7777";

  socket_init(&server);

  socket_bind_and_listen(&server, hostname, servicename);

  client_t client;
  socket_t peer = client->sockt;

  socket_accept(&server, &peer);

  //socket_receive(&client, buffer, sizeof(buffer));

  socket_uninit(&server);
}