#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>



int main(int argc, char *argv[]) {

	int _port = 8081;
	char *host = "localhost";
	char *message_fmt = "POST /apikey=%s&command=%s HTTP/1.0 \r\n\r\n";

	struct hostent *server;
	struct sockaddr_in serv_addr;
	int sockfd, bytes, sent, received, total;
	char message[1024], response[4096];

	sprintf(message, message_fmt, "key1", "comand1");
	printf("Request: \n%s\n", message);	

	// create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == -1) {
		perror("Could not create socket");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_addr.s_addr = inet_addr(host);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(_port);

	if (connect (sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("Connect failed");
		exit(1);
	}	

	total = strlen(message);
	sent = 0;

	do {
		bytes = write(sockfd, message+sent, total-sent);
		if (bytes < 0) perror("ERROR writing message to socket");
		if (bytes == 0) break;
		sent += bytes;
	} while (sent < total);

	memset(response, 0, sizeof(response));

	total = sizeof(response) -1;
	received = 0;

	do {
		bytes = read(sockfd, response+received, total-received);
		if (bytes < 0) perror("ERROR reading response from socket");
		if (bytes == 0) break;
		received +=bytes;
	} while (received < total);

	if (received == total) 
		perror ("ERROR storing complete response from socket");

	close(sockfd);
	printf("Reponse: \n%s\n", response);
	
	exit(0);	

}
