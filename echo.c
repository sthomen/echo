#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ADDRESS "127.0.0.1"
#define PORT 7
#define MSGSIZE 11

int main(int argc, char **argv)
{
	char *message="Hello World\n";
	char buffer[MSGSIZE];

	int sock;
	struct sockaddr_in sa;

	sa.sin_family=AF_INET;
	sa.sin_port=htons(PORT);

	printf("Converting address to a network number: ");
	if (inet_aton(ADDRESS, &sa.sin_addr)!=1) {
		printf("Couldn't interpret address: %s\n", strerror(errno));
		exit(1);
	}
	printf("Ok\n");

	printf("Opening socket: ");
	if ((sock=socket(PF_INET, SOCK_STREAM, 0))==-1) {
		printf("Couldn't create socket: %s\n", strerror(errno));
		exit(2);
	}
	printf("Ok\n");

	printf("Connecting: ");
	if (connect(sock, (struct sockaddr *)&sa, sizeof(sa))) {
		printf("Couldn't connect: %s\n", strerror(errno));
		exit(3);
	}
	printf("Ok\n");

	printf("Writing message: ");
	if (write(sock, message, MSGSIZE)==-1) {
		printf("Couldn't write: %s\n", strerror(errno));
		exit(4);
	}
	printf(message);

	printf("Reading message: ");
	if (read(sock, &buffer, MSGSIZE)==-1) {
		printf("Couldn't read: %s\n", strerror(errno));
		exit(5);
	}

	printf("%s\n", buffer);

	close(sock);

	return 0;
}

