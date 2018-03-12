/* 

This sender is 251

*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <math.h>

#include<signal.h>
#include <sys/types.h>

// include get_info.cpp
#include "get_info.h"

using namespace std;

// declare my message buffer
struct buf 
{
	long mtype; // required
	char greeting[50]; // mesg content
};


int main() 
{

	// find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	//For Receiver 1
	bool play = true;
	while(play)
	{
		//randomly creating 32 bit values numbers
		int r = rand() % ((int) pow(2,32) - 1);
		msg.mtype = 251; 	
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
		cout<<"251 sent to Receiver 1 Number :"<<r<<endl;
		msgrcv(qid, (struct msgbuf *)&msg, size, 251, 0); // reading
	}
	

	//get_info function
	get_info(qid,  (struct msgbuf *)&msg, size, 112);

	cout<<"Sender 251 terminated"<<endl;
	exit(0);
	
}



