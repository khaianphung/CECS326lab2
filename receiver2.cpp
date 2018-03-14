/* 

This is the second receiver

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
	// find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	//use this code to test receiver2, sender 997, and sender 257 by themselves
	//int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	
	int counter = 0;
	int switchmtype = ; 
	
	bool sender997 = true;
	bool sender257 = true;

	while(counter < 5000)
	{
		//swapping the mtype parameter for the msgrcv function
		if( (sender997 == true && switchmtype == 257) || sender257 == false)
		{
			switchmtype = 9972;
		}	
		else if( (sender257 == true && switchmtype == 9972) || sender997 == false )
		{
			switchmtype = 257;
		}
		else
		{
			switchmtype = IPC_NOWAIT;
		}
		
		//getting a message
		if (msgrcv(qid, (struct msgbuf *)&msg, size, switchmtype, 0) >= 0)
		{
			if(msg.mtype == 9972)
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

					strcpy(msg.greeting, "Ack from Receiver 2");
					msg.mtype = 222; 
					msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				}
			}
			else if(msg.mtype == 257)
			{
				//display sender number
				cout << "Sender 257: " << msg.greeting << endl;
			}

			counter++;
		}

		//displaying counter
		cout<<"Counter: "<<counter<<endl;

		//checking to see if sender 997 and 257 are still active
		cout << "boolSender997: " << sender997 << endl;
		cout << "boolSender257: " << sender257 << endl; 
		
	}

	//sending one last message to sender 997
	msg.mtype = 222; 
	strcpy(msg.greeting, "Receiver 2 has terminated");
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);

	//sending exit event to sender 257
	msg.mtype = 333; 
	strcpy(msg.greeting, "Receiver 2 has terminated");
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	
	//display that receiver 2 has terminated
	cout << "Receiver 2 terminated" << endl;
	
	exit(0);
}


