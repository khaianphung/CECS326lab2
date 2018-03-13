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
	while (play)
	{
		//getting a 997 message
		if (msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0) >= 0)
		{
			if(msg.greeting == "Sender 997 terminated")
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

		//getting a 251 message
		if(msgrcv(qid, (struct msgbuf *)&msg, size, 251, 0) >= 0)
		{
			
			if(msg.greeting == "Sender 251 terminated")
			{
				cout << msg.greeting << endl;
				sender251 = false;
			}
			else
			{
				cout << "Sender 251: " << msg.greeting << endl;
			}
		}
		

		if(sender997 == false && sender251 == false)
		{
			play = false;
		}			
		//if both sender 997 and 251 are terminated
		//if (msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0) < 0 && 
		//    msgrcv(qid, (struct msgbuf *)&msg, size, 251, 0) < 0) 
		//{
		//	exit(0);
		//}
	}

	cout<<"Receiver 1 terminated"<<endl;
	exit(0);
}


