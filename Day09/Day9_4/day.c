
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
	char *ptr;
	int i,ret1,ret2,ret3,ret4,ret6,ret5,err,s1, s2, s3, s4,s5,s6;
	ret1 = fork();
	if(ret1 == 0)
	{
		char file[16]="circle.c";
		char cmd[10] = "gcc";
		char *args[] = {cmd,"-c",file,NULL};
		err = execvp(cmd,args);
		printf("Circle.c is compiled using child 1\n");
		_exit(0);
	}
	ret2 = fork();
	if(ret2 == 0)
	{
		char file[16]="square.c";
		char cmd[10] = "gcc";
		char *args[] = {cmd,"-c",file,NULL};
		err = execvp(cmd,args);
		printf("square.c is compiled using child 2\n");
		_exit(0);
	}
	ret3 = fork();
	if(ret3 == 0)
	{
		char file[16]="rectangle.c";
		char cmd[10] = "gcc";
		char *args[] = {cmd,"-c",file,NULL};
		err = execvp(cmd,args);
		printf("rectangle.c is compiled using child 3\n");
		_exit(0);
	}
	ret4 = fork();
	if(ret4 == 0)
	{
		char *args[] = {"gcc","-c","main.c",NULL};
		err = execvp("gcc",args);
		printf("main.c is compiled using child 4\n");
		_exit(0);
	}
	waitpid(ret1,&s1,0);
	waitpid(ret2,&s2,0);
	waitpid(ret3,&s3,0);
	waitpid(ret4,&s4,0);
	if(s1 != 0 || s2 != 0 || s3 != 0 || s4 != 0) {
		printf("compiler errors...\n");
		_exit(0);
	}
	ret5 = fork();
	if(ret5 == 0)
	{

		char *args[] = {"gcc","-o","program.out","rectangle.o","square.o","circle.o","main.o",NULL};
		err = execvp("gcc",args);
		printf("rectangle.o square.o circle.o main.o Are compiled using child 5\n");
		_exit(0);	

	}
	waitpid(ret5,&s5,0);
	if(s5 != 0)
	{
		printf("Linker error...\n");
	}
	ret6 = fork();
	if(ret6 == 0)
	{
		char *args[] = {"./program.out",NULL};
		err = execv("/home/Desktop/eos/day9/DAy9_4/program.out",args);
		printf("Program is executed using child 6\n");
		_exit(0);

	}
	waitpid(ret6,&s6,0);
	if(s6 != 0)
	{
		perror("Program execution is failed...");
	}
	printf("Bye Bye !!\n");
	return 0;
}

