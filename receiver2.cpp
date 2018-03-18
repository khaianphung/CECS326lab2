/* 
Khai Phung
Tam Tran
Vincent Vu
Bunly Buth

filename: receiver2.cpp
This is the second receiver. This receiver receives messages from sender 257 and sender 997. 
While receiving messages from those senders, the receiver ONLY sends back acknowledgement to
sender 997. The receiver's termination condition is that the receiver receives 5000 messages.

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
	bool terminate;		//Check for termination
	
};

int main() 
{
	// find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	//use this code to test receiver2, sender 997, and sender 257 by themselves
	//int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	//counter: variable to keep track of the amount of messages received.
	//switchmtype: the parameter for the msgrcv function
	int counter = 0;
	//int switchmtype = 257; 
	
	//Variables keep track of whether the senders have terminated
	bool sender997 = true;
	bool sender257 = true;

	//Main loop
	while (counter < 50000000)//5000 is too low
	{		
		//receiving message
		msgrcv(qid, (struct msgbuf *)&msg, size, 222, 0);
		//cout<<"Counter: "<<counter<<endl;
		
		if(msg.needAck == true )			//message from sender 997
		{
			
			if(msg.terminate == true) 	//checking for termination
			{
				sender997 = false;
			}
			else				//sender still active
			{
				cout << "Sender 997: " << msg.greeting << endl;
				strcpy(msg.greeting, "Ack from Receiver 2");
				msg.mtype = 333; 	//mtype for sending ack message
				msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				
			}			
			
			
		}
		else if(msg.needAck == false )	// message from sender 257
		{
			
			if(strcmp(msg.greeting, "Sender 257 terminated") == 0)
			{
				//cout << msg.greeting << endl;
				sender257 = false;
			}
			else
			{
				cout << "Sender 257: " << msg.greeting << endl;
			}
		}
		

		counter++;
		//checking if loop end because senders are terminated , not because exceed 5000 messages
		//cout << "boolSender997: " << sender997 << endl;
		//cout << "boolSender257: " << sender257 << endl;  		
	}


	///
	/// delete all msg with mtype 222 in queue
	///	
	//display that receiver 1 has terminated
	cout<<"Receiver 2 terminated"<<endl;
	exit(0);
}


