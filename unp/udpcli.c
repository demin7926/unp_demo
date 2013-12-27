#include "mh.h"

void dg_cli(FILE *fp, int sockfd, SA* servaddr, int len);

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc!=3 || !atoi(argv[2])){
		fprintf(stderr, "Usage:%s ip port\n", argv[0]);
		return ME_USAGE;
	}

	if( (sockfd=socket(AF_INET, SOCK_DGRAM, 0))<0 ){
		perror("socket fail");
		return ME_NET;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));

	return 0;
}

void dg_cli(FILE *fp, int sockfd, SA *pservaddr, int len)
{
	int n;
	char buf[MAXLINE];

	while(fgets(buf, MAXLINE, fp)!=NULL){
		sendto(sockfd, buf, strlen(buf), 0,  pservaddr, len);
		n = recvfrom(sockfd, buf, MAXLINE, 0, NULL, NULL);	
		buf[n] = 0;
		fputs(buf, stdout);
	}
}
