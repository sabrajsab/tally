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
	freeaddrinfo(res);
	printf("client: connections...\n");
	

	connect(sd, res->ai_addr, res->ai_addrlen);
	
		char msg[100];
		int  msg_len = 100;
	memset(msg, '\0', msg_len);
	printf ("\nenter msg to send : ");
	scanf ("%s", &msg);
	send(sd, msg, msg_len, 0);
	close(sd);
	return 0;
}
