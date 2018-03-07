/* 

This is a simple illustration of the use of:
	ftok, msgget, msgsnd, msgrcv

Program B creates a message queue to be shared with Program A.
Then, they will pass messages back and forth.

Program A sends the first message and reads the reply. Program A
also sends a "fake" message to the msgQ that will never be read
by Program B.

Both child processes use message type mtype = 113 and 114.

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

int main() {

	// create my msgQ with key value from ftok()
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

	// declare my message buffer
	struct buf {
		long mtype; // required
		char greeting[50]; // mesg content
	};

	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	
	int counter = 0;
	while(counter <5000){
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
	exit(0);
}


