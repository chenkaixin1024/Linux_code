#include "comm.h"

struct msgbuf
{
	long msgtype;
	char mtext[1024];
};

int CreateMsgQueue()
{
	key_t key=ftok("/tmp",0);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}

	int msgqid=msgget(key,IPC_CREAT);
	if(msgqid<0)
	{
		perror("msgget");
		return -1;
	}

	return msgqid;
}

int Destory(int msgqid)
{
	return msgctl(msgqid,IPC_RMID,NULL);
}


int SendMsg(int msgqid,char* text)
{
	struct msgbuf mb;
	memcpy(mb.mtext,text,strlen(text)+1);
	mb.msgtype=1;
	if(msgsnd(msgqid,(void*)&mb,sizeof(mb)-sizeof(long),0)<0)
	{
		perror("msgsnd");
		return -1;
	}

	printf("send: %s\n",text);

	return 0;
}


int RecvMsg(int msgqid)
{
	struct msgbuf mb;
	if(msgrcv(msgqid,(void*)&mb,sizeof(mb)-sizeof(long),1,0)<0)
	{
		perror("msgrcv");
		return -1;
	}

	printf("rev: %s\n",mb.mtext);
	return 0;
}



