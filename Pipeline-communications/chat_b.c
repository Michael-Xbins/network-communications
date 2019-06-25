#include "func.h"

int main(int argc,char**argv)
{
	check_args(argc,3);
	int fdw,fdr;
	fdw=open(argv[1],O_WRONLY);
	if(-1==fdw)
	{
		perror("open");
		return -1;
	}
	fdr=open(argv[2],O_RDONLY);
	printf("fdw=%d,fdr=%d\n",fdw,fdr);

	//消息队列
	int msg_id=msgget(1000,0600|IPC_CREAT);
	check_error(-1,msg_id,"msgget");

	char buf[128];
	fd_set rdset;
	int ret;
	struct msgbuf msg;
	memset(&msg,0,sizeof(msg));

	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(fdr,&rdset);
		ret=select(fdr+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			memset(buf,0,sizeof(buf));
			if(FD_ISSET(fdr,&rdset))
			{
				ret=read(fdr,buf,sizeof(buf));
				if(0==ret)			
				{
					printf("byebye\n");
					return -1;
				}
				msg.mtype=1;
				strcpy(msg.mtext,buf);
				msgsnd(msg_id,&msg,strlen(msg.mtext),0);
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				read(0,buf,sizeof(buf));
				write(fdw,buf,strlen(buf)-1);
			}
		}
	}

	return 0;
}
