#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, char *argv[])
{
	int sockfd;
	socklen_t len;
	struct sockaddr_un	addr1, addr2;

	if(argc!=2){
		fprintf(stderr, "Usage:%s path\n", argv[0]);
		return -3;
	}

	unlink(argv[1]);
	
	if( (sockfd=socket(AF_LOCAL, SOCK_STREAM, 0))<0 ){
		perror("socket() fail");
		return -1;
	}

	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_LOCAL;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path)-1);
	//if( bind(sockfd, (struct sockaddr *)&addr1, sizeof(addr1))<0 ){
	if( bind(sockfd, (struct sockaddr *)&addr1, SUN_LEN(&addr1))<0 ){
		perror("bind() fail");
		return -1;
	}

	//test
	printf("\nsizeof:%d\nSUN_LEN:%d\n\n", sizeof(addr1), SUN_LEN(&addr1));

	len = sizeof(addr2);
	getsockname(sockfd, (struct sockaddr *)&addr2, &len);
	printf("bound name=%s, ori len=%d, return len=%d\n", 
		addr2.sun_path, sizeof(addr2), len);

	return 0;
}
