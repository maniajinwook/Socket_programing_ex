#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7777   /* 포트 번호 */
#define BUFSIZE 1024

main()
{
	int sockfd;
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	char recvBuffer[BUFSIZE];
	char sendBuffer[BUFSIZE];
	int clntLen;
	int recvLen;
	int temp = 0;

	/* 인터넷으로 연결된 프로세스들 간에 통신을 하고 UDP 방법을 이용하는 소켓을 생성 */
	if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("sock failed");
		exit(1);
	}

	/* servAddr를 0으로 초기화 */
	memset(&servAddr, 0, sizeof(servAddr));
	/* servAddr에 IP 주소와 포트 번호를 저장 */
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	/* sockfd 소켓에 주소 정보 연결 */
	if(bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
		perror("bind failed");
		exit(1);
	}

	/* 무한 반복 */
	while(1) {
		clntLen = sizeof(clntAddr);
	
		temp++;
		//printf("Input sending message ==> ");
		//fgets(sendBuffer, BUFSIZE, stdin);
		sprintf(sendBuffer,"%d",temp);
		//if(!strncmp(sendBuffer, "quit", 4))
		//	break;

		/* sockfd 소켓을 통해 servAddr을 주소로 갖는 서버에게 데이터를 보냄 */
		if(sendto(sockfd, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*)&clntAddr, sizeof(clntAddr)) != strlen(sendBuffer)) {
			perror("sendto failed");
			exit(1);
		}
		if(temp == 100)
			temp = 0;
		
		/* 받은 데이터를 출력 */
		//printf("Recevied: %s\n", recvBuffer);
	}
}






