#pragma once

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>

int CreateMsgQueue();
int Destory(int msgqid);
int SendMsg(int msgqid,char* text);
int RecvMsg(int msgqid);

