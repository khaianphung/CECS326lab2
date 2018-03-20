/* 
Bunly Buth
Khai Phung
Tam Tran
Vincent Vu

filename: receiver2.cpp

This is the second receiver. This receiver receives messages from sender 257 and sender 997. While receiving messages from those senders, the receiver ONLY sends back acknowledgement to sender 997. The receiver's termination condition is that the receiver receives 5000 messages.

*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

// declare my message buffer
struct buf 
{
	long mtype;		// required
	char greeting[50]; 	// mesg content
	bool needAck;		// check if message needs an acknowledgement back
	bool terminate;		// used to check for termination
	
};

int main() 
{
	// find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	//counter: variable to keep track of the amount of messages received.
	int counter = 0;

	// This while loop receives messages with mtype 111 which are sent from sender 997 and 257
	// this loop ends after 5000 messages
	while (counter < 50000)
	{		
		//receiving message
		msgrcv(qid, (struct msgbuf *)&msg, size, 222, 0);

		//checking if this message was from sender 997
		if(msg.needAck == true)			
		{
				//display message and send ack msg
				cout << "Sender 997: " << msg.greeting << endl;
				strcpy(msg.greeting, "Ack from Receiver 2");
				msg.mtype = 444; 	//mtype for sending ack message
				msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			
		}
		//checking if this message was from sender 257, if so display message
		else 
		{
				cout << "Sender 257: " << msg.greeting << endl;
		}
		
		counter++;	
	}

	//Since receiver 2 is about to terminate, send termination message to sender 997
	strcpy(msg.greeting, "Receiver 2 has terminated");
	msg.mtype = 444; 	//mtype for sending ack message
	msg.terminate = true;	//setting termination
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);

	//Since receiver 2 is about to terminate, also terminate sender 257
	system("pkill sender257.out");
	cout << "Sent termination event to sender 257" << endl;

	//terminating receiver 2
	cout<<"Receiver 2 terminated"<<endl;
	exit(0);
}
