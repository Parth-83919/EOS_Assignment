#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	
	int num1, num2, n1, n2, sum ,res,ret, s, arr1[2], arr2[2];
	
	ret = pipe(arr1);
	ret = pipe(arr2);

	ret = fork();
	if(ret == 0){
		//child
		printf("enter the two num: ");
		scanf("%d %d", &n1, &n2);

		close(arr1[0]);
		close(arr2[1]);

		write(arr1[1], &n1, sizeof(n1));
		write(arr1[1], &n2, sizeof(n2));

		read(arr2[0], &res, sizeof(res));

		printf("child: result: %d\n",res);
		
		close(arr1[1]);
		close(arr2[0]);
	}
	else{
		//parent
		close(arr1[1]);
		close(arr2[0]);

		read(arr1[0], &num1, sizeof(num1));
		read(arr1[0], &num2, sizeof(num2));
		
		printf("parent: num1: %d\n",num1);
		printf("parent: num2: %d\n",num2);
		
		sum = num1 + num2;

		printf("parent: sum: %d\n",sum);

		write(arr2[1], &sum, sizeof(sum));

		close(arr1[0]);
		close(arr2[1]);

		waitpid(-1, &s, 0);
	}

	return 0;
}
