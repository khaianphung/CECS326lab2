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
	long mtype; // required
	char greeting[50]; // mesg content
};

int main() 
{

	// create the message queue
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

	

	buf msg;
	int size = sizeof(msg)-sizeof(long);

	bool play = true;
	bool sender997 = true;
	bool sender251 = true;
	int switchmtype = 997; 

	while (play)
	{		
		//swapping the mtype parameter for the msgrcv function
		if( (sender997 == true && switchmtype == 251) || sender251 == false)
		{
			switchmtype = 997;
		}	
		else if( (sender251 == true && switchmtype == 997) || sender997 == false )
		{
			switchmtype = 251;
		}
		else
		{
			switchmtype = IPC_NOWAIT;
		}
		
		//getting a 997 message
		if (msgrcv(qid, (struct msgbuf *)&msg, size, switchmtype, 0) >= 0)
		{
			if(msg.mtype == 997)
			{
				if(strcmp(msg.greeting, "Sender 997 terminated") == 0)
				{
					cout << msg.greeting << endl;
					sender997 = false;
				}
				else
				{
					cout << "Sender 997: " << msg.greeting << endl;

					//sending ack message
					strcpy(msg.greeting, "Ack from Receiver 1");
					msg.mtype = 111; 
					msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				}
			}
			else if(msg.mtype == 251)
			{
				if(strcmp(msg.greeting, "Sender 251 terminated") == 0)
				{
					cout << msg.greeting << endl;
					sender251 = false;
				}
				else
				{
					cout << "Sender 251: " << msg.greeting << endl;
				}
			}
				
		}

		
		if(sender997 == false && sender251 == false)
		{
			play = false;
		}
		
		//checking to see if sender 997 and 251 are still active
		cout << "boolSender997: " << sender997 << endl;
		cout << "boolSender251: " << sender251 << endl;  		
	}

	cout<<"Receiver 1 terminated"<<endl;
	exit(0);
}


