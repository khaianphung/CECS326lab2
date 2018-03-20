/* 
Bunly Buth
Khai Phung
Tam Tran
Vincent Vu

filename: sender3.cpp (sender 257)

This is sender 257. Sender 257 repeatedly sends a random 32 bit value to receiver 2.
Sender 257 terminates when receiver 2 terminates.

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
	long mtype; 		// required identifier
	char greeting[50]; 	// mesg content
	bool needAck;		// to know if receiver needs to send an ack msg to sender 257
	bool terminate;		// used to check for termination
	

};

int main() 
{
	
	// find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	bool play = true;
	while(play)
	{
		// randomly creating 32 bit values numbers
		int r = rand() % ((int) pow(2,32) - 1);		
		
		// change char array to string
		string c = to_string(r);			
		
		//checking amount of messages in queue 
		struct msqid_ds buf;
		int checking = msgctl(qid, IPC_STAT, &buf);

		// to prevent programs from stopping because of message queue being full
		// only send messages when queue has less than 250 messages
		if(buf.msg_qnum < 250) 
		{
			//sending 257 message
			msg.mtype = 222; 				// changing mtype to send to receiver 2
			msg.needAck = false;				// this sender does not need ack messages		
			msg.terminate = false;				// not terminate yet
			strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending back the same 257 message
		}
		
		// display random number
		cout << r << endl;		
	}
	
	//terminating sender 257
	cout<<"Sender 257 terminated"<<endl;
	exit(0);
}

			
