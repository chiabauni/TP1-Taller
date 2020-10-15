#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "socket.h"

#define SOCKTS_EN_COLA 10

int socket_init(socket_t *self) {
	self->s = -1;

	return 0;
}


int socket_uninit(socket_t *self) {
	socket_close(self);
	
	self->s = -1;

	return 0;
}


int socket_bind_and_listen(socket_t *self, const char *host, const char *service) {
	int status = 0;

	struct addrinfo hints;
   	
   	struct addrinfo *results, *ptr;
	
	memset(&hints, 0, sizeof(struct addrinfo));
   	
   	hints.ai_family = AF_INET;       
   	
   	hints.ai_socktype = SOCK_STREAM; 
   	
   	hints.ai_flags = AI_PASSIVE;              

   	status = getaddrinfo(NULL, service, &hints, &results); 

	socket_status_error(self, status);

   	for (ptr = results; ptr != NULL; ptr = ptr->ai_next) {
   		self->s = socket(ptr->ai_family, ptr->ai_socktype,
   					ptr->ai_protocol);
   		
   		if (self->s == -1) continue;

   		if (bind(self->s, ptr->ai_addr, ptr->ai_addrlen) == 0){
   			printf("Conexion exitosa\n");
   			
   			break;
   		}

   		close(self->s);
   	}

   	if (ptr == NULL) {     
   		fprintf(stderr, "Conexion fallida\n");

   		socket_close(self);
        
        return 1;
    }

   	freeaddrinfo(results);

   	status = listen(self->s, SOCKTS_EN_COLA);

   	socket_status_error(self, status);

   	return 0;
}


int socket_accept(socket_t *listener, socket_t *peer) {
	int accepted = accept(listener->s, NULL, NULL); 

	//socket_status_error(listener, status);
	//fprintf(stderr, "Todo OK\n");

   	peer->s = accepted;
   	
   	return 0;
}


int socket_connect(socket_t *self, const char *host, const char *service) {
	int status = 0;

	struct addrinfo hints;
   	
   	struct addrinfo *results, *ptr;
	
	memset(&hints, 0, sizeof(struct addrinfo));
   	
   	hints.ai_family = AF_INET;       
   	
   	hints.ai_socktype = SOCK_STREAM; 
   	
   	hints.ai_flags = 0;              

   	status = getaddrinfo(host, service, &hints, &results); 

   	socket_status_error(self, status);

   	int val = 1;
   	setsockopt(self->s, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

   	for (ptr = results; ptr != NULL; ptr = ptr->ai_next) {
   		self->s = socket(ptr->ai_family, ptr->ai_socktype,
   					ptr->ai_protocol);
   		
   		if (self->s == -1) continue;

   		if (connect(self->s, ptr->ai_addr, ptr->ai_addrlen) != -1) {
   			printf("Conexion exitosa\n");
   			
   			break;
   		}

   		close(self->s);
   	}

   	if (ptr == NULL) {     
   		fprintf(stderr, "Conexion fallida\n");
        
        socket_close(self);

        return 1;
    }

   	freeaddrinfo(results);

   	return 0;
}


ssize_t socket_send(socket_t *self, char *buffer, size_t lenght) {
	int n = 0;

	while (n < lenght) {
		int status = send(self->s, buffer, lenght-n, MSG_NOSIGNAL);

		if (status == -1){
			printf("Error: %s\n", strerror(errno));

			socket_close(self);
			
			return 1;
		} else {
			n += status;
		}
	}
}


ssize_t socket_receive(socket_t *self, char *buffer, size_t buffer_size) {
	int status = 0;

	for(int pos = 0; pos < buffer_size; pos += status){
		int status = recv(self->s, &buffer[pos], buffer_size-pos, 0);
		
		if (status == 0) {
			fprintf(stderr, "Error:%s\n", strerror(status)); 
   			
   			socket_close(self);
		} else if (status == -1) {
			socket_status_error(self,status);
		}
	}
}

void socket_close(socket_t *self) {
	shutdown(self->s, SHUT_RDWR);
	
	close(self->s);
}

int socket_status_error(socket_t *self, int status) {
   	if (status != 0) {
   		fprintf(stderr, "Error:%s\n", strerror(status)); //chequear si quiero pasarlo por stderr
   		
   		socket_close(self);

   		return 1;
   	}

   	return 0;
}