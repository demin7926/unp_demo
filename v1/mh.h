#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <wait.h>
#include <time.h>
#include <errno.h>

#define ME_NET		-10
#define ME_IO		-11
#define ME_USAGE	-12
#define ME_OTHER	-12

#define LISTENQ		5
#define MAXLINE		256
#define	SA			struct sockaddr

typedef void Sigfunc(int);

//functions declare
Sigfunc* m_signal(int signo, Sigfunc *func);
