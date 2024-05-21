#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>

//client
#define SOCKET_PATH "/tmp/socket_desd"
int main(int argc, char*argv[]){

	int sum,cli_fd, ret, num1, num2;
	struct sockaddr_un cli_addr;
	socklen_t socklen;

	if( argc != 3){
		printf("invalid cmd line args.\n");
		_exit(1);
	}

	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);

	cli_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(cli_fd < 0){
		perror("socket() failed");
		_exit(2);
	}

	cli_addr.sun_family = AF_UNIX;
	strcpy(cli_addr.sun_path,SOCKET_PATH);
	ret = connect(cli_fd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
	if(ret < 0){
		perror("connect() failed");
		_exit(3);
	}


	
		
		write(cli_fd, &num1, sizeof(num1));
		write(cli_fd, &num2, sizeof(num2));
		
		printf("send data: num1: %d num2: %d\n",num1,num2);

		read(cli_fd, &sum, sizeof(sum));

		printf("sum: %d\n",sum);

		

	close(cli_fd);

	return 0;
}
