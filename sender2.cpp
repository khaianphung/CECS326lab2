/* 
Khai Phung
Vincent Vu
Tam Tran

filename: sender2.cpp (sender 251)
This sender is sender 251. Sender 251's job is to send a random 32 bit number to 
receiver 1. It's continues to send until the user kills the program
using a kill command. On kill command, the program sends one last message to notify 
the receiver 1 that it has terminated.

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
	//play: Condition for main loop to continue
	bool play = true;
	//Main loop
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



