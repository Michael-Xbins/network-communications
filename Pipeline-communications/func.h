#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>
#include<grp.h>
#include<pwd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<assert.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/msg.h>
#include<signal.h>
#include<pthread.h>
#include<sys/epoll.h>
#include<sys/socket.h>
#include<netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <syslog.h>


#define check_args(argc,num){if(argc!=num){printf("error args\n");\
	return -1;}}

#define check_error(ret_val ,ret ,func_name){if(ret_val==ret){\
	perror(func_name);return -1;}}

#define check_thread_error(ret,func_name){if(0!=ret){\
	printf("%s is failed %d\n",func_name,ret);return -1;}} 

struct protocol
{
	int flag; 		//4个字节
	char buf[4092]; //刚好总共用了4096字节
};

struct msgbuf
{
	long mtype;
	char mtext[64];
};
