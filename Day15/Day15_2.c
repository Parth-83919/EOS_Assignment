#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

struct array{
	int *arr;
	int size;
};

void* bubbleSort(void *param){
	struct array *ptr = (struct array*)param;
	
	printf("sorting array inside thread.\n");
	for(int i=0; i < ptr->size - 1; i++){
		for(int j=0; j < ptr->size-i-1;j++){
			if(ptr->arr[j] > ptr->arr[j+1]){
				int temp = ptr->arr[j];
				ptr->arr[j] = ptr->arr[j+1];
				ptr->arr[j+1] = temp;
			}
		}
	}
	
	
	return NULL;
}

int main(){
	int ret;
	pthread_t t1;
	struct array arr;
	int ar[]={64, 34, 25, 12, 22, 11, 90, 78, 56, 33};

	arr.arr = ar;
	arr.size = sizeof(ar)/sizeof(ar[0]);
	printf("size of array: %d\n",arr.size);	
	
	ret = pthread_create(&t1,NULL,bubbleSort, &arr);
	if(ret < 0){
		perror("pthread_create() failed");
		_exit(1);
	}
	
	pthread_join(t1,NULL);

	printf("main thread: sorted array: \n");
	for(int i=0; i < arr.size; i++){
		printf("%d  ",arr.arr[i]);
	}
	printf("\n");

	return 0;
}
