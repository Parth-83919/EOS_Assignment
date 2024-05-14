#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include"square.h"
#include"rectangle.h"
#include"circle.h"

int main(){
	int side,len,wid,rad,err,ret1,ret2,ret3,ret4,s1,s2,s3,s4;

	side=2,len=4,wid=5,rad=2;
	printf("parent start\n");
	ret1 = fork();
	if( ret1 == 0){
		//child process 1
		char *args[]= {"gcc", "-c", "circle.c", NULL};
		err = execvp("gcc",args);
		if(err < 0){
			perror("exec() failed");
			_exit(1);
		}	
	}
	ret2 = fork();
	if(ret2 == 0){
		//child process 2
		char *args[]={"gcc","-c","square.c", NULL};
		err = execvp("gcc",args);
		if(err < 0){
			perror("exec() failed");
			_exit(1);
		}
	}
	ret3 = fork();
	if(ret3 == 0){
		//child process 3
		char *args[]={"gcc","-c","rectangle.c", NULL};
		err = execvp("gcc",args);
		if(err < 0){
			perror("exec() failed");
			_exit(1);
		}
	}
	ret4 = fork();
	if(ret2 == 0){
		//child process 4
		char *args[]={"gcc","-c","main.c", NULL};
		err = execvp("gcc",args);
		if(err < 0){
			perror("exec() failed");
			_exit(1);
		}
	}
	else{
		for(int i=1;i<=10;i++){
			printf("%d",i);
			sleep(1);
		}
		waitpid(-1,&s1,0);
		printf("Child 1 exit : %d\n",WEXITSTATUS(s1));
		waitpid(-1,&s2,0);
		printf("Child 2 exit : %d\n",WEXITSTATUS(s2));
		waitpid(-1,&s3,0);
		printf("Child 3 exit : %d\n",WEXITSTATUS(s3));
		waitpid(-1,&s4,0);
		printf("Child 4 exit : %d\n",WEXITSTATUS(s4));
	}
		
	printf("parent ended\n");



























	//printf("area of circle : %d\n",cir_area(rad));
	//printf("area of square : %d\n",squ_area(side));
	//printf("area of rectangle : %d\n",rec_area(len,wid));

}
