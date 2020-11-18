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
#include <fcntl.h>
#define PORT "9876"

int main()
{   
		struct addrinfo hints, *res;
		int status, sd, new_fd = -1;
		struct sockaddr_storage their_addr;
		socklen_t addr_size;
		struct sigaction sa;
		char msg[100] = "Hello from server\n";
		int  msg_len = 100;
		
	memset (&hints, 0, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo("localhost", PORT, &hints, &res);
	sd = socket(res -> ai_family, res -> ai_socktype, res -> ai_protocol);
	fcntl(sd, F_SETFL, O_NONBLOCK);
	bind(sd, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	listen(sd, 1);
	printf("server: waiting for connections...\n");
	while (new_fd < 0) {
	    new_fd = accept(sd, (struct sockaddr *)&their_addr, &addr_size);
		printf("loop 1\n");
		//sleep(1);
	}
	
	fcntl (new_fd, F_SETFL, O_NONBLOCK);
	while (recv(new_fd, msg, sizeof(msg), 0) < 0) {
		printf("loop 2\n");
		//sleep(1);
	}
	printf("%s", msg);
	close(new_fd);
	close(sd);
	return 0;
}
