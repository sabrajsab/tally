#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT "9876"

int main()
{   
		struct addrinfo hints, *res;
		int status, sd, new_fd;
		struct sockaddr_storage their_addr;
		socklen_t addr_size;
		struct sigaction sa;
		
	memset (&hints, 0, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	getaddrinfo("localhost", PORT, &hints, &res);
	sd = socket(res -> ai_family, res -> ai_socktype, res -> ai_protocol);
	bind(sd, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	listen(sd, 1);
	printf("server: waiting for connections...\n");

	new_fd = accept(sd, (struct sockaddr *)&their_addr, &addr_size);
	
		char msg[100];
		int  msg_len = 100;
	while (msg[0] != '-' || msg [1] != '1') {
		memset(&msg, '\0', msg_len);	
		recv(new_fd, msg, msg_len, 0);		
		printf ("%s\n", msg);	
		send(new_fd, msg, msg_len, 0);
	}
	close(new_fd);

	
	close(sd);
	return 0;
}