#include "mh.h"

void dg_echo(int sockfd, SA* cliaddr, int len);

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in  servaddr, cliaddr;

	if(argc!=2 || !atoi(argv[1])){
		fprintf(stderr, "Usage:%s port\n", argv[0]);
		return ME_USAGE;
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0){
		perror("socket fail");
		return ME_NET;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	if( bind(sockfd, (SA*)&servaddr, sizeof(servaddr))<0 ){
		perror("bind fail");
		return ME_NET;
	}

	dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr));

	return 0;
}

void dg_echo(int sockfd, SA* pcliaddr, int len)
{
	char buf[MAXLINE];
	int clilen, n;

	for( ;; ){
		clilen = len;
		n = recvfrom(sockfd, buf, MAXLINE, 0, pcliaddr, &clilen);
		sendto(sockfd, buf, n, 0, pcliaddr, clilen);
	}
}
