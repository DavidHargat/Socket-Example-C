#include <stdio.h>
#include <stdlib.h>

#include "socklib.h"

void handle_socket(int sock){
	// attempt to read 256 bytes from the socket to a buffer.
	char *buffer = sl_read(sock, 256);
	// print the bytes as a string.
	printf("\n%s\n", buffer);
	// echo the same bytes.
	write(sock, buffer, strlen(buffer));
	// free the memory from the buffer.
	free(buffer);
}

// NOTES
//  bzero sets a block of memory to zero, it's used throughout this program to avoid undefined behavior
//  though it's probably optional

int main(int argc, char **argv)
{
	int port = 1024;

	// Server and client socket identifiers.
	int server_socket, client_socket;
	
	// Server and client addresses.
	struct sockaddr *server_address, *client_address; 
	
	// Allocate space for the client's address
	client_address = sl_sockaddr();
	// Allocate and initialize a server address
	server_address = sl_sockaddr_server(port);
	// bind a TCP server socket.
	server_socket = sl_tcp_server(server_address);
	
	// Accept new socket connections,'handle' them, close.
	while( 1 ){
		client_socket = sl_accept(server_socket, client_address);
		handle_socket(client_socket);
		close(client_socket);
	}
	
	// Close the server
	close(server_socket);
	
	// Free the memory from the server/client addresses
	free(server_address);
	free(client_address);

	return 0; 
}
