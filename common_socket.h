#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H
#include <stdio.h>
#include <stdbool.h>
#include "common_cipher.h"
//-------------------------------------------------------------------------
typedef struct{
	int fd;
	struct addrinfo* results_getaddr;
} socket_t;

/* Recibe un socket_t, inicializa el client_t y lo atributos correspondientes
 si no hay errores devuelve 0 sino devuelve -1 */
int socket_init(socket_t *self);

/* Recibe un socket_t, destruye el socket liberando los recursos utilizados,
si no hay errores devuelve 0 sino devuelve -1 */
int socket_uninit(socket_t *self);

/* Recibe un socket_t, el host, el port y un booleano que indica si se trata 
de un server(true) o no. Aplicando el getaddrinfo se obtiene la lista 
de direcciones sobre las cuales se intentara la conexion. Si no hay errores
 devuelve 0 sino devuelve -1 */
int socket_get_addresses(socket_t *self, const char *host, 
						const char *service, bool is_server);

/* Recibe un socket_t y enlaza el socket con el resultado obtenido en 
get_addresses. Si no hay errores devuelve 0 sino devuelve -1 */
int socket_bind(socket_t *self);

/* Recibe un socket_t y establece el servidor a la escucha de clientes
(en este caso como se debe conectar unicamente con uno, solo hay un lugar
 en la cola de espera). Si no hay errores devuelve 0 sino devuelve -1 */
int socket_listen(socket_t *self);

/* Recibe un socket_t aceptador(server) y un socket_t peer correspondiente 
al cliente, acepta una conexion entrante. Si no hay errores devuelve 0 
sino devuelve -1 */
int socket_accept(socket_t *listener, socket_t *peer);

/* Recibe un socket_t que intenta conectarse con el resultado obtenido en 
get_addresses. Si no hay errores devuelve 0 sino devuelve -1 */
int socket_connect(socket_t *self);

/* Recibe un socket_t, un buffer y longitud de bytes a enviar a traves 
del socket. Si no hay errores devuelve 0 sino devuelve -1 */
int socket_send(socket_t *self, char* buffer, size_t buffer_size);

/* Recibe un socket_t, un buffer y longitud de bytes a recibir a traves 
del socket. Si no hay errores devuelve 0 sino devuelve -1 */
ssize_t socket_receive(socket_t *self, char* buffer, int buffer_size);

/* Recibe un socket_t y cierra el canal solicitado del socket, liberando
 los recursos utilizados. Si no hay errores devuelve 0 sino devuelve -1 */
int socket_close(socket_t *self);
//-------------------------------------------------------------------------
#endif
