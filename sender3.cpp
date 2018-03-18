/* 
Tam Tran
Khai Phung
Vincent Vu
Bunly Buth

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
	bool terminate;		//used to check for termination
	

};

int main() 
{
	
	// find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	
	msg.mtype = 222;
	strcpy(msg.greeting,"Sender 257 terminated");
	msg.needAck = false;				// this sender does not need ack messages
	msg.terminate = true;
	


	bool play = true;
	while(play)
	{
		int r = rand() % ((int) pow(2,32) - 1);		// randomly creating 32 bit values numbers
		string c = to_string(r);			// change char array to string
		
		//does not start until 997 starts
		// this makes it so that it controls how many messages are coming from sender 257
		if(msgrcv(qid, (struct msgbuf *)&msg, size, 222, 0) >= 0)
		{
			if(msg.needAck == true) //if this a message is from  997, then send it back in the queue
			{
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// send msg 997 back so that receiver1 will read it

				//sending our a new 257 message
				msg.mtype = 222; 				// changing mtype to send to receiver 2
				msg.needAck = false;				// this sender does not need ack messages		
				msg.terminate = false;				// not terminate yet
				strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending back the same 257 message
			}	
			else	//send message back 
			{
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending back the same 257 message
\
			}
		}
		else	//if there are no mtype 222 in queue, then send a mtype 222 message
		{
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// a new 251 message
		}
		
		
		cout << r << endl;		// display random number
	}
	
	cout<<"Sender 257 terminated"<<endl;
	exit(0);
	
}


