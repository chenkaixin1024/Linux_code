#include "comm.h"

int main()
{
	int msgqid=CreateMsgQueue();
	if(msgqid<0)
		return -1;
	while(1)
	{
		sleep(2);
		if(RecvMsg(msgqid)<0)
			return -1;
	}

	Destory(msgqid);
	return 0;
}


