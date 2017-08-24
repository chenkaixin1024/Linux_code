#include "comm.h"


int main()
{
	int msgqid=CreateMsgQueue();
	if(msgqid<0)
		return -1;

	while(1)
	{
		sleep(2);
		char buf[]="hello,I am sedMsg";
		if(SendMsg(msgqid,buf)<0)
			break;
	}

	Destory(msgqid);

	return 0;
}



