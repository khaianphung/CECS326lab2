/* 

first receiver 

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

	msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0); // read mesg
						// don't read "fake" mesg
	cout << getpid() << ": gets message" << endl;
	cout << "message: " << msg.greeting << endl;
	
	strcat(msg.greeting, " and Adios.");
	cout << getpid() << ": sends reply" << endl;
	msg.mtype = 997; // only reading mesg with type mtype = 314
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);

	
	
	msgrcv(qid, (struct msgbuf *)&msg, size, 251, 0); // read mesg
						// don't read "fake" mesg
	cout << getpid() << ": gets message" << endl;
	cout << "message: " << msg.greeting << endl;
	
	strcat(msg.greeting, " and Adios.");
	cout << getpid() << ": sends reply" << endl;
	msg.mtype = 251; // only reading mesg with type mtype = 314
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	
	//terminate program
	exit(0);
}


