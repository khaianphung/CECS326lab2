/* 

This is the first receiver

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
	long mtype; 		// required identifier
	char greeting[50]; 	// mesg content
	bool needAck;		// to know if receiver needs to send an ack msg to sender 997
	bool terminate;		//used to check for termination
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

	//mtype for receiver 1 is 111
	while (play)
	{		
		//receiving message
		msgrcv(qid, (struct msgbuf *)&msg, size, 111, 0);
		
		if(msg.needAck == true)			//message from sender 997
		{
			if(msg.terminate == false) 	//checking for termination
			{
				cout << "Sender 997: " << msg.greeting << endl;

				strcpy(msg.greeting, "Ack from Receiver 1");
				msg.mtype = 333; 
				msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			}	
			else				//sender still active
			{
				sender997 = false;
			}
			
		}
		else					// message from sender 251
		{
			if(msg.terminate == false) 	//checking for termination
			{
				cout << "Sender 251: " << msg.greeting << endl;
			}
			else				//sender still active
			{
				sender251 = false;
			}
		}

		//if both senders are terminated
		if(sender997 == false && sender251 == false)
		{
			play = false;
		}
		
		//checking to see if sender 997 and 251 are still active
		cout << "boolSender997: " << sender997 << endl;
		cout << "boolSender251: " << sender251 << endl;  		
	}


	///
	/// delete all msg with mtype 111 in queue
	///	
	//display that receiver 1 has terminated
	cout<<"Receiver 1 terminated"<<endl;
	exit(0);
}


