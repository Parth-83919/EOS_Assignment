#include<stdio.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
	int n1,n2,fd_w,fd_r,cnt1,cnt2,cnt3,res;

	fd_r = open("/tmp/fifo1",O_RDONLY);
	if( fd_r < 0){
		perror("open() fifo1 failed");
		_exit(1);
	}

	fd_w = open("/tmp/fifo2",O_WRONLY);
	if( fd_w < 0){
		perror("open() fifo2 failed");
		_exit(1);
	}
	
	cnt1 = read(fd_r, &n1, sizeof(n1));
	cnt2 = read(fd_r, &n2, sizeof(n2));

	printf("server received data: \n");
	printf("n1: %d\nn2: %d\n",n1,n2);
	
	res = n1+n2;

	cnt3 = write(fd_w, &res, sizeof(res));

	printf("server send data bytes: %d\n",cnt3);
	
	close(fd_w);
	close(fd_r);
	return 0;
}
