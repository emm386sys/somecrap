// Client side implementation of UDP client-server model
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

// Driver code


unsigned long convertTime(struct timeval time){
	return time.tv_sec*1000000 + time.tv_usec;
}

int crap() {
	int sockfd;
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, len;

	struct timeval start,end;
	gettimeofday(&start,NULL);
	unsigned long startUs = convertTime(start);

	sendto(sockfd, &startUs, sizeof(startUs),
			MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));

	n = recvfrom(sockfd, &start, sizeof(start),
			MSG_WAITALL, (struct sockaddr *) &servaddr,
			&len);

	gettimeofday(&end,NULL);
	unsigned long end_usec = convertTime(end);

	printf("total %ld usec\n",end_usec - startUs);

	close(sockfd);
	return 0;
}

int main(){
	for(int i=0;i<10000;i++){
		crap();
		usleep(500);
	}
}
