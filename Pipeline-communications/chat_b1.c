#include"func.h"
int main()
{
	int flag=0;
	
	//消息队列
	int msg_id=msgget(1000,0600|IPC_CREAT);
	struct msgbuf msg;
	while(1)
	{
		bzero(&msg,sizeof(msg));
		msgrcv(msg_id,&msg,sizeof(msg.mtext),1,0);
		printf("%s\n",msg.mtext);
	}
	return 0;
}
