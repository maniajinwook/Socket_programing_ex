#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 7777   /* 서버의 포트 번호 */
#define BUFSIZE 1024

/* argv[1]은 수와 점 표기의 IP 주소 */
main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servAddr;
    char sendBuffer[BUFSIZE], recvBuffer[BUFSIZE];
    int recvLen;

    if(argc != 2) {
       fprintf(stderr, "Usage: %s IP_address\n", argv[0]);
       exit(1);
    }

    /* 소켓 생성 */
    if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1) {
       perror("sock failed");
       exit(1);
    }

    memset(&servAddr, 0, sizeof(servAddr));
    /* servAddr에 IP 주소와 포트 번호를 저장 */
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(PORT);

    /* servAddr 서버에 통신을 요청 */
    if(connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
       perror("connect failed");
       exit(1);
    }

    /* quit를 입력 받을 때까지 반복 */
    while(1) {
       printf("Input sending message ==> ");
       fgets(sendBuffer, BUFSIZE, stdin);
       if(!strncmp(sendBuffer, "quit", 4))
          break;

       /* sockfd 소켓을 통해 데이터를 보냄 */
       if(send(sockfd, sendBuffer, strlen(sendBuffer), 0) != strlen(sendBuffer)) {
          perror("send failed");
          exit(1);
       }

       /* sockfd 소켓을 통해 들어오는 데이터를 받아 recvBuffer에 저장 */
       if((recvLen=recv(sockfd, recvBuffer, BUFSIZE-1, 0)) <= 0) {
          perror("recv failed");
          exit(1);
       }

       recvBuffer[recvLen] = '\0';
       /* 받은 데이터를 출력 */
       printf("Recevied: %s\n", recvBuffer);
    }
    /* sockfd 소켓을 닫음 */
    close(sockfd);
    exit(0);
}
