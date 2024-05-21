#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* selec_sort(void *param){
	int *arr=(int*)param;
	for(int i=0; i<10;i++){
		for(int j=i+1; j<10; j++){
			if(arr[i] > arr[j]){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	printf("thread completed sorting\n");
	return NULL;
}

int main(){
	int ret, arr[]={77,3,5,9,12,57,9,87,90,16};
	pthread_t t1;
	ret = pthread_create(&t1, NULL, selec_sort, arr);
	if(ret != 0){
		perror("pthread_create() failed");
		_exit(1);
	}
	pthread_join(t1,NULL);
	printf("main thread: sorted array: \n");
	for(int i=0; i<10; i++){
		printf("%d\n",arr[i]);
	}
	printf("press enter to exit\n");
	getchar();
	return 0;
}
