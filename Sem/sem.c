#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short int* array;
	struct seminfo* _buf;
};

int main()
{
	key_t key=ftok("/tmp",0);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}

	int semid=semget(key,1,IPC_CREAT|IPC_EXCL);
	if(semid<0)
	{
		perror("semget");
		return -1;
	}

	union semun sm;
	sm.val=1;
	if(semctl(semid,0,SETVAL,sm)<0)
	{
		perror("semctl");
		return -1;
	}

	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_flg=SEM_UNDO;

	pid_t pid=fork();
	if(pid>0)
	{
		while(1)
		{
			sb.sem_op=-1;
			semop(semid,&sb,1);
			sleep(rand()%3);
			printf("a");
			fflush(stdout);
			sb.sem_op=1;
			semop(semid,&sb,1);
		}
		waitpid(pid,NULL,0);
	}
	else
	{
		while(1)
		{
			sb.sem_op=-1;
			semop(semid,&sb,1);
			sleep(rand()%3);
			printf("b");
			fflush(stdout);
			sb.sem_op=1;
			semop(semid,&sb,1);
		}
	}

	semctl(semid,0,IPC_RMID);

	return 0;
}


