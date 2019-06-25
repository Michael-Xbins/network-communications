#include "func.h"

void sigfunc(int signum)
{
	printf("%d\n",signum);
}

int main(int argc,char**argv)
{
	check_args(argc,3);
	int fdr,fdw;

	//管道
	fdr=open(argv[1],O_RDONLY);
	if(-1==fdr)
	{
		perror("open1");
		return -1;
	}
	fdw=open(argv[2],O_WRONLY);
	printf("fdr=%d,fdw=%d\n",fdr,fdw);

	int ret;
	fd_set rdset;

	//共享内存
	int shmid=shmget(1000,4096,0600|IPC_CREAT);
	struct protocol *p;
	p=shmat(shmid,NULL,0);
	memset(p,0,4096);

	//信号量
	int semid=semget(1000,1,0600|IPC_CREAT);
	semctl(semid,0,SETVAL,1);
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;

	//信号
	signal(SIGINT,sigfunc);

	char buf[128]={0};
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
					p->flag=2;
					return -1;
				}
				else
				{
					semop(semid,&sopp,1);
					p->flag=1;
					strcpy(p->buf,buf);
					semop(semid,&sopv,1);
				}
			}
			if(FD_ISSET(0,&rdset))
			{
				read(0,buf,sizeof(buf));
				write(fdw,buf,strlen(buf)-1);
			}
		}
	}

	return 0;
}

