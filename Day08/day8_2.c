#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	
	int a,b,c,d,i,s1,s2,s3,s4;
for(i=1;i<=5;i++){
	a=fork();
	if(a == 0){
		b=fork();
		if(b == 0){
			c=fork();
			if(c == 0){
				d=fork();
				if(d == 0){
					printf("count : %d\n",i);
					//printf("Parent process : %d child process: %d",getppid(),getpid());
					sleep(1);
					_exit(0);
				}
				waitpid(d,&s4,0);
				printf("child d: %d\n",s4);
				//printf("Parent process : %d child process: %d",getppid(),getpid());
				sleep(1);
				_exit(0);
			}
			waitpid(c,&s3,0);
			printf("child c: %d\n",s3);
			//printf("Parent process : %d child process: %d\n",getppid(),getpid());
			sleep(1);
			_exit(0);
		}
		waitpid(b,&s2,0);
		printf("child b: %d\n",s2);
		//printf("Parent process : %d child process: %d\n",getppid(),getpid());
		sleep(1);
		_exit(0);
	}
	waitpid(a,&s1,0);
	printf("child a: %d\n",s1);
	sleep(1);

}
	printf("Parent process\n");

	return 0;
}
