#include "mh.h"

void str_cli(FILE *fp, int sockfd);

int main(int argc, char *argv[]){
	int sockfd;
	int servport;
	struct sockaddr_in servaddr;

	if(argc!=3 || !(servport=atoi(argv[2])) ){
		fprintf(stderr, "usage:%s ip port\n", argv[0]);
		return ME_USAGE;
	}

	if( (sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1 ){
		perror("socket fail");
		return ME_NET;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(servport);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)!=1 ){
		fprintf(stderr, "Invalid server ip\n");
		return ME_USAGE;
	}

	if( connect(sockfd, (SA*)&servaddr, sizeof(servaddr))==-1 ){
		perror("connect fail");
		return ME_NET;
	}

	str_cli(stdin, sockfd);

	return 0;
}


void str_cli(FILE *fp, int sockfd)
{
	char line[MAXLINE];
	size_t n;

	while(fgets(line, MAXLINE, fp)){
		write(sockfd, line, strlen(line));
		
		//reading the echo from server
		bzero(line, MAXLINE);
		if( (n=read(sockfd, line, MAXLINE))<-0 ){
			break;
		}
		printf("%s\n", line);
	}	
}
