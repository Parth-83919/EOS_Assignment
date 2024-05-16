#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/wait.h>

#define MQ_KEY 0x1111

typedef struct msg{
	long type;
	int n1[2];
}msg_t;

typedef struct msg2{
	long type;
	int sum;
}msg_t2;

int main(){
	int mqid, ret, s;
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid < 0){
		perror("msgget() failed");
		_exit(1);
	}

	ret = fork();
	if(ret == 0){
		msg_t m1;
		m1.type = 1;

		printf("Enter two number:");
		for(int i=0; i<2; i++){
			scanf("%d",&m1.n1[i]);
		}

		ret = msgsnd(mqid, &m1, sizeof(m1)-sizeof(m1.type) ,0);
		if (ret < 0){
			perror("msgsnd() failed");
			_exit(2);
		}
		printf("child (send): msg send: %d\n",ret);
	
		msg_t2 m3;

		ret = msgrcv(mqid, &m3, sizeof(m3)-sizeof(m3.type),2,0);
		printf("child receive ret = %d\n",ret);
		printf("child sum: %d\n",m3.sum);
	}
	else{
		msg_t m2;
		printf("parent receiver: wainting for msg..\n");
		ret = msgrcv(mqid, &m2, sizeof(m2)-sizeof(m2.type),1,0);
		printf("parent (receiver): msg received: %d -- n1=%d n2=%d\n", ret, m2.n1[0], m2.n1[1]);
		
		msg_t2 m4;
		m4.type=2;
		m4.sum = m2.n1[0] + m2.n1[1];

		printf("parent: sum: %d\n",m4.sum);
		
		ret = msgsnd(mqid, &m4, sizeof(m4)-sizeof(m4.type),0);
		if( ret < 0){
			perror("msgsnd() failed");
			_exit(2);
		}
		printf("parent send msg: %d\n",ret);

		msgctl(mqid,IPC_RMID, NULL);

		waitpid(ret,&s,0);

	}

	return 0;
}
