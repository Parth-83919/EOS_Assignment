#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int ret,s,fd,err;

	ret = fork();
	if(ret == 0){
		
		fd = open("in.txt",O_RDONLY);
//		close(0);
//		dup(fd);
		dup2(fd,0);//here fd will be copied to 0=STDIN. which means in.txt output is redirected as input and the input goes to wc.
					//if STDIN is not closed and first it will closed then fd will redirected their.
		err = execlp("wc","wc",NULL);
		if(err < 0){
			perror("exec() failed");
			_exit(1);
		}	
	}
	else{
		waitpid(-1,&s,0);
		printf("Exit status of the child: %d\n",WEXITSTATUS(s));
	}	
	return 0;
}
