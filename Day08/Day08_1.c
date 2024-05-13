#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int ret,i,s;
	for(i=1;i<=5;i++){
		ret= fork();
		if(ret == 0){
			for(int j=1; j<=5;j++){
				printf("child: %d count:%d child pid: %d\n",i,j,getpid());
				sleep(1);
			}
			_exit(0);
		}

	}

	for(int i=1; i<=10;i++){
		printf("parent process %d\n",i);
		sleep(1);
	}

	for(int i=1;i<=5;i++){
		waitpid(-1,&s,0);
		printf("child %d exit: %d\n",i,WEXITSTATUS(s));
	}


	return 0;
}
