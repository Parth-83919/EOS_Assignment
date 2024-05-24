#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include"square.h"
#include"rectangle.h"
#include"circle.h"

int main(){
	int err,ret1,ret2,ret3,ret4,ret5,ret6,s1,s2,s3,s4,s5,s6;

//	printf("parent started\n");
	ret1 = fork();
	if( ret1 == 0){
		//child process 1
		char *args[]= {"gcc", "-c", "circle.c", NULL};
		err = execvp("gcc",args);
		if(err < 0){
			perror("exec1() failed");
			_exit(1);
		}
		printf("child 1 execute\n");
	}
	ret2 = fork();
	if(ret2 == 0){
		//child process 2
		char *args[]={"gcc","-c","square.c", NULL};
		err = execvp("gcc",args);
		if(err < 0){
			perror("exec2() failed");
			_exit(1);
		}
		printf("child 2 execute\n");
	}
	ret3 = fork();
	if(ret3 == 0){
		//child process 3
		char *args[]={"gcc","-c","rectangle.c", NULL};
		err = execvp("gcc",args);
		if(err < 0){
			perror("exec3() failed");
			_exit(1);
		}
		printf("child 3 execute\n");
	}
	ret4 = fork();
	if(ret4 == 0){
		//child process 4
		char *args[]={"gcc","-c","main.c", NULL};
		err = execvp("gcc",args);
		if(err < 0){
			perror("exec4() failed");
			_exit(1);
		}
		printf("child 4 execute\n");
	}
	waitpid(ret1,&s1,0);
	waitpid(ret2,&s2,0);
	waitpid(ret3,&s3,0);
	waitpid(ret4,&s4,0);

	if( s1!=0 || s2!=0 || s3!=0 || s4!=0){
		printf("compier error..\n");
		_exit(0);
	}
	ret5= fork();
	if(ret5 == 0){
		char *args[]={"gcc", "-o", "program.out", "circle.o", "square.o", "rectangle.o", "main.o",NULL};
		err = execvp("gcc",args);
		if(err<0){
			perror("exec5() failed");
			_exit(1);
		}
		printf("child 5 execute\n");
	}

	waitpid(ret5,&s5,0);
	if( s5 != 0){
		printf("linker error..\n");
		_exit(3);
	}
	ret6 = fork();
	if(ret6 == 0){
		char *args[]={"./program.out",NULL};
		//err = execl("/home/parth/Desktop/eos/day9/Day9_4/program.out","./program.out",NULL);
		err = execv("/home/parth/Desktop/eos/day9/Day9_4/program.out",args);
		if(err<0){
			perror("exec6() failed");
			_exit(1);
		}
		printf("child 6 execute\n");
	}


	waitpid(ret6,&s6,0);
	if(s6!=0){
		perror("program execution failed\n");
		_exit(4);
	}	
	printf("parent ended\n");

	return 0;

}
