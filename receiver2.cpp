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
/*
	msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0); // read mesg

	cout << getpid() << ": gets message" << endl;
	cout << "message: " << msg.greeting << endl;
	
	strcat(msg.greeting, " and Adios.");
	cout << getpid() << ": sends reply" << endl;

	msg.mtype = 997; // only reading mesg with type mtype = 314
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	
*/
	
		msgrcv(qid, (struct msgbuf *)&msg, size, 257, 0); // read mesg
	
						
		cout << getpid() << ": gets message" << endl;
		cout << "message: " << msg.greeting << endl;
	
		strcat(msg.greeting, " and Adios.");

		cout << getpid() << ": sends reply" << endl;

		cout<<"Counter: "<<counter<<endl;

		msg.mtype = 257; 
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	
		counter++;
	}

	cout << "Receiver2 terminated" << endl;
	exit(0);
}


