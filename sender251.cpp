/* 
sender 251
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

	// search for the queue
	int qid = msgget(ftok(".",'u'), 0);

	// declare my message buffer
	struct buf {
		long mtype; // required
		char greeting[50]; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	
	strcpy(msg.greeting, "Hello there");	
	cout << getpid() << ": sends greeting" << endl;
	msg.mtype = 251; 	// set message type mtype = 251
	msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending

	msgrcv(qid, (struct msgbuf *)&msg, size, 251, 0); // reading
	cout << getpid() << ": gets reply" << endl;
	cout << "reply: " << msg.greeting << endl;
	cout << getpid() << ": now exits" << endl;

}
