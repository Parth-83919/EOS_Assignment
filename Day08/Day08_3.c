#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	
	int ret,j,s,i,k;
	i=1;
	while(1)
	{
		ret=fork();
		if(ret == 0){
			 k=1;
			_exit(0);
		}
		else if(ret == -1)
			break;
		else{
			i++;
			printf("child count: %d\n",i);
		}
	}

	for(j=1; j<=i ; j++){
		wait(&s);
	}


	return 0;
}
