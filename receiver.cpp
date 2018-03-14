/* 
Tam Tran
Khai Phung
Vincent Vu
Bunly Buth

filename: receiver1.cpp
This is the first receiver. This receiver's role is to create the queue and receive messages from 
both sender 257 and sender 997. While receiving messages from those senders, the receiver also 
sends back an acknowledgement message to them beforce continuing. The program terminates when 
both senders terminate.

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
	long mtype; // required
	char greeting[50]; // mesg content
};

int main() 
{

	// create the message queue
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	//condition for staying in the loop
	bool play = true;

	//used for checking if senders have terminated
	bool sender997 = true;
	bool sender251 = true;
	int switchmtype = 9971; 

	//Main loop
	while (play)
	{		
		//swapping the mtype parameter for the msgrcv function
		if( (sender997 == true && switchmtype == 251) || sender251 == false)
		{
			switchmtype = 9971;
		}	
		else if( (sender251 == true && switchmtype == 9971) || sender997 == false )
		{
			switchmtype = 251;
		}
		else
		{
			//switchmtype when used in the msgrcv function checks for a message immediately. If message of 
			//mtype is not in queue, sends back -1.
			switchmtype = IPC_NOWAIT;
		}
		
		//getting a message
		if (msgrcv(qid, (struct msgbuf *)&msg, size, switchmtype, 0) >= 0)
		{
			//message from sender 997
			if(msg.mtype == 9971)
			{	
				//if sender 997 have terminated
				if(strcmp(msg.greeting, "Sender 997 terminated") == 0)
				{
					cout << msg.greeting << endl;
					sender997 = false;
				}
				else	//send acknowledgement to sender 997
				{
					//display sender number
					cout << "Sender 997: " << msg.greeting << endl;

					strcpy(msg.greeting, "Ack from Receiver 1");
					msg.mtype = 111; 
					msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				}
			}
			//message from sender 251
			else if(msg.mtype == 251)
			{	
				//check if sender 251 have terminated
				if(strcmp(msg.greeting, "Sender 251 terminated") == 0)
				{
					cout << msg.greeting << endl;
					sender251 = false;
				}
				else
				{
					//display sender number
					cout << "Sender 251: " << msg.greeting << endl;
				}
			}
				
		}

		//if both senders are terminated
		if(sender997 == false && sender251 == false)
		{
			//Ends the main loop
			play = false;
		}
		
		//checking to see if sender 997 and 251 are still active
		cout << "boolSender997: " << sender997 << endl;
		cout << "boolSender251: " << sender251 << endl;  		
	}

	//display that receiver 1 has terminated
	cout<<"Receiver 1 terminated"<<endl;
	exit(0);
}


