/* 

This is sender 257

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
using namespace std;

// declare my message buffer
struct buf 
{
	long mtype; // required
	char greeting[50]; // mesg content
};

int main() 
{
	
	// find exisiting queue
	int qid = msgget(ftok(".",'u'), 0);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);


	bool play = true;
	while (play)
	{

		
		int r = rand() % ((int) pow(2,32) - 1); 	//randomly creating 32 bit values numbers
		string c = to_string(r);			//change char array to string
		msg.mtype = 257; 				//changing mtype to send to receiver 2
		strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg
		cout << r << endl;				//display random number

		//checking if receiver 2 is terminated
		if (msgrcv(qid, (struct msgbuf *)&msg, size, 333, IPC_NOWAIT) >= 0)
		{
			//terminates program
			cout<<"Sender 257 terminated"<<endl;
			exit(0);
		}
		else if(msgrcv(qid, (struct msgbuf *)&msg, size, 257, IPC_NOWAIT) < 0) //if this haven't sent a message yet, then send one
		{
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
		}	
	
	}

	exit(0);
}


