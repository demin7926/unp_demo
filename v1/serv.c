#include "mh.h"

void str_echo(int connfd);

int main(int argc, char **argv)
{
	pid_t pid;
	int listenfd, connfd;
	int port, clilen;
	struct sockaddr_in	servaddr, cliaddr;
	
	if(argc!=2 || !(port=atoi(argv[1]))){
		printf("Usage: %s port\n", argv[0]);
		return ME_USAGE;
	}

	if( (listenfd=socket(AF_INET, SOCK_STREAM, 0))==-1 ){
		printf("socket faile");
		return ME_NET;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));
	if(bind(listenfd, (SA*)&servaddr, sizeof(servaddr))==-1){
		perror("bind fail");
		return ME_NET;
	}

	if(listen(listenfd, LISTENQ)==-1){
		perror("listen fail");
		return ME_NET;
	}

	while(1){
		connfd = accept(listenfd, (SA*)&cliaddr, &clilen);
	
		if( (pid=fork())==0 ){
			//child process
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		
		close(connfd);
	}

	return 0;
}


void str_echo(int connfd){
	size_t n;
	char line[MAXLINE];
	for(;;){
		if( (n=read(connfd, line, MAXLINE))==0 ){
			return;		//connect closed by the other end
		}
		write(connfd, line, n);
	}
}
