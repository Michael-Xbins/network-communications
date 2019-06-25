#include"func.h"

int main()
{
	//共享内存
	int shmid=shmget(1000,4096,0600|IPC_CREAT);
	printf("shmid=%d\n",shmid);
	struct protocol *p;
	p=shmat(shmid,NULL,0);
	//信号量
	int semid=semget(1000,2,0600|IPC_CREAT);
	semctl(semid,0,SETVAL,1);
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;

	while(1)
	{
		semop(semid,&sopp,1);
		if(p->flag==0)
		{
			semop(semid,&sopv,1);
		}
		else if(p->flag==1)
		{
			printf("%s\n",p->buf);
			p->flag=0;
			semop(semid,&sopv,1);
		}
		else if(p->flag==2)
		{
			break;
		}
	}
	return 0;
}
