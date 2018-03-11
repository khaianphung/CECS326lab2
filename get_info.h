#include<iostream>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>

void get_info(int qid, msgbuf *exitmsg, int size, long mtype);

// declare my message buffer
struct buf 
{
	long mtype; // required
	char greeting[50]; // mesg content
};

void get_info(int qid, msgbuf *exitmsg, int size, long mtype)
{
	buf msg;
	strcpy(msg.greeting,"Sender 251 has terminated");	
}
