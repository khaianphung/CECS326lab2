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

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	//get_info function
	msg.mtype = 251;
	strcpy(msg.greeting, "Sender 251 terminated");
	get_info(qid,  (struct msgbuf *)&msg, size, 251);


	//For Receiver 1
	bool play = true;
	while(play)
	{
		int r = rand() % ((int) pow(2,32) - 1);		//randomly creating 32 bit values numbers
		string c = to_string(r);			//change char array to string
		msg.mtype = 251; 				//changing mtype to send to receiver 1
		strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg

		//if this haven't sent a message yet, then send one
		if(msgrcv(qid, (struct msgbuf *)&msg, size, 251, IPC_NOWAIT) < 0)
		{
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
		}	
		
		cout<< r << endl;				//display random number
	}
	
	cout<<"Sender 251 terminated"<<endl;
	exit(0);
	
}



