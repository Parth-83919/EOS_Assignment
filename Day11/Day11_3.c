#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sigint_handler(int sig){
	printf("SIGINT caught\n");
	_exit(1);
}
int main(){
	int arr[2],err, ret, a=1, count=0;
	
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	err = sigaction(SIGINT, &sa, NULL);
	if(err < 0){
		perror("sigaction() failed");
		_exit(3);
	}
	ret = pipe(arr);

	while(1){
		write(arr[1], &a, sizeof(a));
		count++;
		printf("bytes written: %d\n",count);
	}
	return 0;
}
