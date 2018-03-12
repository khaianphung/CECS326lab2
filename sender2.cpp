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
		string c = to_string(r);
		msg.mtype = 251; 	
		strcpy(msg.greeting,c.c_str()); // putting randomized number into the msg
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
		cout<<r<<endl;
	}
	

	//get_info function
	get_info(qid,  (struct msgbuf *)&msg, size, 112);

	cout<<"Sender 251 terminated"<<endl;
	exit(0);
	
}



