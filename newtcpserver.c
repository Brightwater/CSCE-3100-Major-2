#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>
#include <time.h>

void dostuff (int sock);
void printTable(int *ranArr, int *boolArr);

int main(int argc, char *argv[]) {
	int sockfd, client1, client2, portno, clilen, pid, n;
	char buffer[256];
	int ranArr[25];
	int boolArr[25];
	createTickets(ranArr, boolArr);
	printTable(ranArr, boolArr);
	struct sockaddr_in serv_addr, cli_addr;
	fd_set fds; 
	
	if  (argc < 2) {
		fprintf(stderr, "Error, no port provided\n");
		exit(1);
	}
	
	
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) 
		perror("ERROR opening socket");
	
	
	int optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
	
	
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		perror("ERROR on binding");
	
	listen(sockfd,5);
	
	
	clilen = sizeof(cli_addr);
	
	
	
	printf("0 clients connected. Waiting on CLIENT 1 to connect.\n");
	
	if ((client1 = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
		perror("accept");
		exit(1);
	}

	printf("1 client connected . Waiting on CLIENT 2 to connect.\n");
	
	/* Accept another connection. */
	if ((client2 = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
		perror("accept");
		exit(1);
	}
	
	printf("2 clients connected. Ready for incoming requests...\n");
	
	
	
	
	int maxfd = (client1 > client2 ? client1 : client2) + 1;
	int clientready;
	int clientread;
	
	
	while(1) {
		FD_ZERO(&fds);
		FD_SET(client1, &fds);
		FD_SET(client2, &fds);
		
		clientready = select(maxfd, &fds, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0);
		bzero(buffer,256);
		if(FD_ISSET(client1, &fds)) {
			clientread = recv(client1, buffer, sizeof(buffer), 0);
			if(clientread < 1) {
				close(client1);
				close(client2);
				exit(0);
			}
			/*
			
			this is where everyones code will probably go maybe. i also have no idea
			
			
			
			
			
			
			
			
			
			
			
			*/
			printf("Client 1: %s", buffer);
			strcpy(buffer, "Got your message");
			clientread = send(client1, buffer, strlen(buffer), 0);
			
		}
		
		
		bzero(buffer,256);
		if(FD_ISSET(client2, &fds)) {
			clientread = recv(client2, buffer, sizeof(buffer), 0);
			if(clientread < 1) {
				close(client1);
				close(client2);
				exit(0);
			}
			/*
			
			
			this is where everyones code will proabably go maybe.
			
			
			
			
			
			
			
			
			
			*/
			printf("Client 2: %s", buffer);
			bzero(buffer,256);
			strcpy(buffer, "Got your message");
			clientread = write(client2, buffer, strlen(buffer), 0);
		}
		
		
	}
	
	
	
	
	
	
	/*while (1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) 
			perror("ERROR on accept");
			pid = fork();
		if (pid < 0)
			perror("ERROR on fork");
		if (pid == 0)  {
			close(sockfd);
			dostuff(newsockfd);
			exit(0);
		}
		else close(newsockfd);
	}*/
	
	/*bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
		printf("Here is the message: %s\n",buffer);
		
	n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");	
	*/
	
	return 0;
}


void dostuff (int sock) {
	int n;
	char buffer[256];
	  
	bzero(buffer,256);
	n = read(sock,buffer,255);
	if (n < 0) error("ERROR reading from socket");
		printf("Here is the message: %s\n",buffer);
	n = write(sock,"I got your message",18);
	if (n < 0) 
		error("ERROR writing to socket");
}

int createTickets(int *ranArr, int *boolArr)
{
	// variables to hold min and max $ amount for tickets
	int min = 200, max = 400; 
	 
	// seed rand()
	srand(time(NULL));
	
	// generate random number between min and max and put it in the array[i]
	int i; 
	for (i = 0; i < 25; i++) 
	{
            int ranNum = (rand() % (max - min + 1)) + min;
            ranArr[i] = ranNum;
	} 
	
	for (i = 0; i < 25; i++)
	{
		boolArr[i] = 1;
	}
}

void printTable(int *ranArr, int *boolArr) {
	printf("[<> SERVER ]: Database Table:\n");
	printf("TICKET NUMBER  PRICE  STATUS\n----------------------------\n");
	int i;
	for (i = 0; i < 25; i++)
	{
		// check ticket status
		char status[5];
		if (boolArr[i] == 0)
		{
			char status[] = "SOLD";
		}
		else
		{
			char status[] = "AVAIL";
		}
		
		// print tickets
		int ticketNum = i;
		printf("[Tkt # %d]: $ %d %s\n", 10000 + ticketNum, ranArr[i], status);
	}
	printf("----------------------------\n");
	
}


	/*int maxfd = (client1 > client2 ? client1 : client2) + 1;
	int clientready;
	int clientread;
	
	strcpy(buffer, "[<> SERVER ]: Database Table:\n");
	clientread = send(client1, buffer, strlen(buffer), 0);
	
	bzero(buffer,256);
	strcpy(buffer, "TICKET NUMBER  PRICE  STATUS\n----------------------------\n");
	clientread = send(client1, buffer, strlen(buffer), 0);
	
	
	int i;
	for(i = 0; i < 25; i++) {
		char *status;
		if (boolArr[i] == 0) {
			status = "SOLD";
		}
		else {
			status = "AVAIL";
		}
		
		// print tickets
		int ticketNum = i;
		char string[256];
		freopen("/dev/null", "a", stdout);
		setbuf(stdout, string);
		bzero(buffer,256);
		printf("[Tkt # %d]: $ %d %s\n", 10000 + ticketNum, ranArr[i], status);
		strcpy(buffer, string);
		clientread = send(client1, buffer, strlen(buffer), 0);
		bzero(buffer,256);
		
	}
	
	
	strcpy(buffer, "----------------------------\n");
	
	clientread = send(client1, buffer, strlen(buffer), 0);
	
	///////////////////////////////////////////////////////
	bzero(buffer,256);
	strcpy(buffer, "[<> SERVER ]: Database Table:\n");
	
	clientread = send(client2, buffer, strlen(buffer), 0);
	bzero(buffer,256);
	strcpy(buffer, "TICKET NUMBER  PRICE  STATUS\n----------------------------\n");
	
	clientread = send(client2, buffer, strlen(buffer), 0);
	

	for(i = 0; i < 25; i++) {
		char *status;
		if (boolArr[i] == 0) {
			status = "SOLD";
		}
		else {
			status = "AVAIL";
		}
		
		// print tickets
		int ticketNum = i;
		char string[256];
		freopen("/dev/null", "a", stdout);
		setbuf(stdout, string);
		bzero(buffer,256);
		printf("[Tkt # %d]: $ %d %s\n", 10000 + ticketNum, ranArr[i], status);
		strcpy(buffer, string);
		clientread = send(client2, buffer, strlen(buffer), 0);
		bzero(buffer,256);
		
	}
	
	
	strcpy(buffer, "----------------------------\n");
	
	clientread = send(client2, buffer, strlen(buffer), 0);*/


