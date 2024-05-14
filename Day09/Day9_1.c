#include<stdio.h>
#include<sys/types.h>
#include<signal.h>

int main(){
	int signum, pid, ret;
	printf("Enter the signal number to kill process: ");
	scanf("%d",&signum);
	printf("Enter the process id : ");
	scanf("%d",&pid);
	
	ret = kill(pid, signum);

	printf("kill return value : %d\n",ret);
	
}
