/* A simple server in the internet domain using TCP
The port number is passed as an argument */

#ifndef SOCKLIB_H
#define SOCKLIB_H

// packages I know
#include <stdlib.h>
#include <string.h>

// packages to research
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


static int sl_socket_error = 0;
static int sl_bind_error = 0;
static int sl_listen_error = 0;

int sl_set_boolean_option(int sock, int option, int value){return setsockopt(sock, SOL_SOCKET, option, &value, sizeof(value));}
int sl_set_reuseaddr(int sock, int v) {return sl_set_boolean_option(sock, SO_REUSEADDR, v);}
int sl_set_broadcast(int sock, int v) {return sl_set_boolean_option(sock, SO_BROADCAST, v);}
int sl_set_keepalive(int sock, int v) {return sl_set_boolean_option(sock, SO_KEEPALIVE, v);}
int sl_set_debug(int sock, int v)     {return sl_set_boolean_option(sock, SO_DEBUG, v);}
int sl_set_oobinline(int sock, int v) {return sl_set_boolean_option(sock, SO_OOBINLINE, v);}

int sl_tcp(){
	return socket(AF_INET, SOCK_STREAM, 0);
}

int sl_udp(){
	return socket(AF_INET, SOCK_DGRAM, 0);
}

// create and return a pointer to a standard configured sockaddr
// (uses internet, accepts from any interface, uses given port).
struct sockaddr *sl_sockaddr_server(int port){
	struct sockaddr_in *adr = malloc(sizeof(struct sockaddr_in));

	bzero(adr, sizeof(*adr)); // initialize serv_addr (set bytes to zero)
	adr->sin_family = AF_INET; // set domain to internet
	adr->sin_addr.s_addr = INADDR_ANY; // accept connections on ANY interface (specified as an IP address)
	adr->sin_port = htons(port); // htons is required to convert port bytes to 'network order'

	return (struct sockaddr *) adr; // Return as a sockaddr (flattened version of sockaddr_in essentially)
}

struct sockaddr *sl_sockaddr(){
	struct sockaddr *s;
	s = malloc(sizeof(struct sockaddr));
	bzero(s, sizeof(*s));
	return s;
}

// Binds a tcp server.
int sl_tcp_server(struct sockaddr *serv_addr){
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0); // Create a socket (Internet, Stream, (TCP))

	if(sock<0){
		sl_socket_error = sock;
		return -1;
	}

	sl_set_reuseaddr(sock, 1); // set a flag to so it doesn't clog up the port

	int bind_result;
	bind_result = bind(sock, serv_addr, sizeof(*serv_addr));

	// Bind the address to the socket (Fails if port is already being used)
	if (bind_result < 0){
		sl_bind_error = bind_result;
		return -1;
	}

	// Mark the socket to accept incoming connections.
	int listen_result = listen(sock, SOCK_STREAM);

	if(listen_result < 0){
		sl_listen_error = listen_result;
		return -1;
	}

	return sock;
}

int sl_udp_server(int port){
	int sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock<0){
		sl_socket_error = sock;
		return -1;
	}

	sl_set_reuseaddr(sock, 1); // set a flag to so it doesn't clog up the port

	struct sockaddr serv_addr = *sl_sockaddr(port); // Create an address for our listener socket

	int bind_result;
	bind_result = bind(sock, &serv_addr, sizeof(serv_addr));

	// Bind the address to the socket (Fails if port is already being used)
	if (bind_result < 0){
		sl_bind_error = bind_result;
		return -1;
	}

	return sock;
}	


// returns a socket file identifier (int) of a connected client.
// (Warning, you lose all the client address information by using this)
// You know, if you wanted that.

int sl_accept(int sock, struct sockaddr *client_address){
	socklen_t client_address_length = sizeof(*client_address);
	bzero(client_address,client_address_length);
	return accept(sock, client_address, &client_address_length);;
}

// read (bsize) bytes from socket (sockfd) 
char *sl_read(int sock, unsigned int bsize){
	int buffer_size = bsize;
	char *buf = malloc(buffer_size); 
	bzero(buf, buffer_size);
	if(read(sock, buf, buffer_size) < 0){
		return NULL;
	}
	return buf;
}
#endif
