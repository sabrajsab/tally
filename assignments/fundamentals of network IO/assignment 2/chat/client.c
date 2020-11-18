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
	
		char msg[100] = "hello from client\n";
		int  msg_len = 100;
	
	if(fork() == 0) {
		
		send(sd, msg, msg_len, 0);
		while (1) {
		
			//printf("client send\n");
			scanf("%s", &msg);
			send(sd, msg, msg_len, 0);
			if(msg[0] == '-' && msg [1] == '1') {
				
			    exit(0);
			}
		}
		
	}
	while(1) {

		//printf("client recv\n");
		memset(&msg, '\0', msg_len);
		recv(sd, msg, msg_len, 0);		
		if(msg[0] == '-' && msg [1] == '1') {
			
			send(sd, msg, msg_len, 0);
			break;
		}
		printf ("server : %s\n", msg);
	}
	//while (wait(NULL) > 0);
	close(sd);
	return 0;
}
