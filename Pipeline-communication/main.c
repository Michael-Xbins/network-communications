#include "func.h"

void sigfunc(int signum,siginfo_t *p,void *p1)
{
	printf("before sleep %d is coming\n",signum);
	sleep(3);
	sigset_t pend;
	sigpending(&pend);
	if(sigismember(&pend,SIGQUIT))
	{
		printf("SIGQUIT is pending\n");
	}else{
		printf("SIGQUIT not is pending\n");
	}
	printf("after sleep %d is coming\n",signum);
}

int main()
{
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction=sigfunc;
	act.sa_flags=SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);  //当前信号处理流程中，会暂时阻塞SIGQUIT信号
	int ret;
	ret=sigaction(SIGINT,&act,NULL);
	check_error(-1,ret,"sigaction");
	while(1);
}


