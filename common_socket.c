#define _POSIX_C_SOURCE 201112L 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include "common_socket.h"
#define SOCKTS_EN_COLA 1
//-------------------------------------------------------------------------
int socket_init(socket_t *self) {
	if (!self) {
		return -1;
	}
	self->fd = -1;		
	return 0;
}

int socket_uninit(socket_t *self) {
	if (shutdown(self->fd, SHUT_RDWR)) {
		return -1;
	}	
	if(close(self->fd)) {
		return -1;
	}		
	return 0;
}

int socket_get_addresses(socket_t *self, const char *host, 
						const char *service, bool is_server) {
	int status = 0;
	struct addrinfo hints;	
	memset(&hints, 0, sizeof(struct addrinfo));   	
   	hints.ai_family = AF_INET;          	
   	hints.ai_socktype = SOCK_STREAM;    	
   	if(is_server){
   		hints.ai_flags = AI_PASSIVE;
   	} else {
   		hints.ai_flags = 0;
   	}              
   	status = getaddrinfo(host, service, &hints, &(self->results_getaddr)); 
   	if (status != 0) {
   		fprintf(stderr, "Error in getaddrinfo:%s\n", gai_strerror(status));   		
   		freeaddrinfo(self->results_getaddr);
   		return -1;
   	}
   	if (is_server) {
   		status = socket_bind(self);
   	} else {
   		status = socket_connect(self);
   	}
   	freeaddrinfo(self->results_getaddr);
   	if (status != 0) {
   		close(self->fd);
   		return -1;
   	}
   	return 0;
}

int socket_bind(socket_t *self) {
	bool connected = false;
	struct addrinfo *ptr;
	for (ptr = self->results_getaddr; ptr != NULL && connected == false; 
    	ptr = ptr->ai_next) {
		self->fd = socket((self->results_getaddr)->ai_family, 
						(self->results_getaddr)->ai_socktype,
    					(self->results_getaddr)->ai_protocol);
	   	if (self->fd == -1) {
	   		fprintf(stderr,"Error in socket_bind: %s\n", strerror(errno));
	   		return -1;  
	   	}
		int val = 1;
	   	if (setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, 
	   		&val, sizeof(val))) {     
	   		fprintf(stderr,"Error in socket_time_wait: %s\n", strerror(errno));       
	        return -1;
	    }
	    if (bind(self->fd, (self->results_getaddr)->ai_addr, 
	    	(self->results_getaddr)->ai_addrlen)) {
	    	fprintf(stderr,"Error in socket_bind: %s\n", strerror(errno));      
	        return -1;
	    } else {
   			connected = true;
   		}
	}
   	return (!connected);
}

int socket_listen(socket_t *self) {
	int status = listen(self->fd, SOCKTS_EN_COLA);
	if(status) {
		fprintf(stderr, "Error in socket_listen:%s\n", strerror(status));
		close(self->fd);
		return -1;
	}
   	return 0;
}

int socket_accept(socket_t *listener, socket_t *peer) {
	int accepted = accept(listener->fd, NULL, NULL); 
	if (accepted == -1) {
		fprintf(stderr, "Error in socket_accept:%s\n", strerror(accepted));
		close(listener->fd);
		return -1;
	}
   	peer->fd = accepted;   	
   	return 0;
}

int socket_connect(socket_t *self) {
	bool connected = false;
	struct addrinfo *ptr;
    for (ptr = self->results_getaddr; ptr != NULL && connected == false; 
    	ptr = ptr->ai_next) {
    	self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
   		if (self->fd == -1) {
   			fprintf(stderr,"Error in socket_connect: %s\n", strerror(errno));       
        	return -1;
   		}
   		if (connect(self->fd, ptr->ai_addr, ptr->ai_addrlen)) {
   			fprintf(stderr,"Error in socket_connect: %s\n", strerror(errno));
   			close(self->fd);
   			return -1;
   		} else {
   			connected = true;
   		}
    }
   	return (!connected);
}

int socket_send(socket_t *self, char* buffer, size_t buffer_size) {
	int n = 0;
	while (n < buffer_size) {
		int status = 0;
		status = send(self->fd, &buffer[n], buffer_size-n, MSG_NOSIGNAL);
		if (status == -1) {
			fprintf(stderr,"Error in socket_send: %s\n", strerror(errno));
			close(self->fd);		
			return -1;
		} else if (status == 0){
			return 0;
		} else {
			n += status;
		}
	}
	return 0;
}

ssize_t socket_receive(socket_t *self, char* buffer, int buffer_size){
	ssize_t n = 0;
	while (n < buffer_size) {
		ssize_t status = recv(self->fd, &buffer[n], buffer_size-n, 0);
		if (status == -1) {
			fprintf(stderr, "Error in socket_receive:%s\n", strerror(status));    			
   			close(self->fd);
   			return -1;
		} else if (status == 0) {
			return n;
		} else {
			n += status;
		}
	}
	return n;
}

