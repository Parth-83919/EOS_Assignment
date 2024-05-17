#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<unistd.h>

int main(){
	int n1,n2,fd_r,fd_w,cnt1,cnt2,res;
	printf("Enter the two number: ");
	scanf("%d%d",&n1,&n2);
	
	fd_w = open("/tmp/fifo1", O_WRONLY);
	if(fd_w < 0){
		perror("open fd_w failed");
		_exit(1);
	}

	fd_r = open("/tmp/fifo2", O_RDONLY);
	if(fd_r < 0){
		perror("open fd_r failed");
		_exit(1);
	}

	cnt1 = write(fd_w, &n1, sizeof(n1));
	cnt2 = write(fd_w, &n2, sizeof(n2));
	
	printf("client send bytes: cnt1:%d cnt2:%d\n",cnt1,cnt2);

	read(fd_r, &res, sizeof(res));
	

	printf("sum: %d + %d = %d\n",n1,n2,res); 

	close(fd_w);
	close(fd_r);
	return 0;
}
