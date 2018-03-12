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


	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	
	int counter = 0;
	while(counter <5000)
	{
		//getting a 997 message
		if (msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0) >= 0 )
		{
			cout << "Sender 997: " << msg.greeting << endl;

			//sending ack message
			strcpy(msg.greeting, "Ack from Receiver 1");
			msg.mtype = 997; 
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			counter++;
		}

		//getting a 257 message
		if (msgrcv(qid, (struct msgbuf *)&msg, size, 257, 0) >= 0)
		{
			cout << "Sender 257: " << msg.greeting << endl;
			counter++;
		}	

		cout<<"Counter: "<<counter<<endl;
	
		
	}

	//probably wrong
	//sending exit event to sender 257
	msg.mtype = 257; 
	strcpy(msg.greeting, "Receiver 1 has terminated");
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	
	cout << "Receiver2 terminated" << endl;
	
	exit(0);
}


