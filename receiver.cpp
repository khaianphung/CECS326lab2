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
	while (play)
	{

		//receive msg from 997
		msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0); 

		// read mesg
		cout<< "Sender 997: " << msg.greeting << endl;

						// don't read "fake" mesg
		//cout << getpid() << ": gets message" << endl;
		//cout << "message: " << msg.greeting << endl;
	

		//creating ack msg for 997
		strcpy(msg.greeting, "Ack from Receiver 1");
		msg.mtype = 997; 
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); //sending ack message
	

	

/*
	msgrcv(qid, (struct msgbuf *)&msg, size, 251, 0); // read mesg
						// don't read "fake" mesg
	cout << getpid() << ": gets message" << endl;
	cout << "message: " << msg.greeting << endl;
	
	strcat(msg.greeting, " and Adios.");
	cout << getpid() << ": sends reply" << endl;
	msg.mtype = 251; // only reading mesg with type mtype = 314
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
*/
	}

	cout<<"Receiver1 terminated"<<endl;
	exit(0);
}


