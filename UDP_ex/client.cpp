#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 7777   /* 서버의 포트 번호 */
#define BUFSIZE 1024

/* argv[1]은 수와 점 표기의 IP 주소 */
main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	char sendBuffer[BUFSIZE], recvBuffer[BUFSIZE];
	int recvLen, servLen;
	int temp;
	temp = 0;
  
	if(argc != 2) {
		fprintf(stderr, "Usage: %s IP_address\n", argv[0]);
		exit(1);
	}

	/* 소켓 생성 */
	if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("sock failed");
		exit(1);
	}

	memset(&servAddr, 0, sizeof(servAddr));
	/* servAddr에 IP 주소와 포트 번호를 저장 */
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(PORT);

	/* quit를 입력 받을 때까지 반복 */
	while(1) {
		
		if((recvLen=recvfrom(sockfd, recvBuffer, BUFSIZE-1, 0, (struct sockaddr*)&servLen,(socklen_t*)&servLen)) == -1) {
			perror("recvfrom failed");
			exit(1);
		}
		recvBuffer[recvLen] = '\0';
		printf("Recevied: %s\n", recvBuffer);

	}
	close(sockfd);
	exit(0);
}




