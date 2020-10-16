#include <stdio.h>
#include "server_socket.h"


#define BUFF_SIZE 64

/*static void _receive_buffer(const char *buffer, 
                      size_t buffer_size,
                      void *callback_ctx) {
  server_t *socket = callback_ctx;
  if (socket_receive(&(self->peer), buffer, buffersize)) {
    return -1;
  }
  return 0;
}*/

int main(int argc, char *argv[]) {
  server_t server;

  //har buffer[BUFF_SIZE];
  
  //const char *hostname = "localhost";

  //const char *servicename = "7777";

  server_init(&server, argv[1]);

  server_connect(&server);

  //server_receive(&server);

  server_uninit(&server);
}