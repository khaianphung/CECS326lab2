/* 

This is a simple illustration of the use of:
	ftok, msgget, msgsnd, msgrcv

Program A will use a message queue created by Program B. 
Then, they will pass messages back and forth.

Program A sends the first message and reads the reply. Program A
also sends a "fake" message to the msgQ that will never be read
by anyone.

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
#include <math.h>
using namespace std;

int main() {

	// pause Program A
	//sleep(3); 	// BAD programming - unreliable and potential bug
			// do NOT use

	int qid = msgget(ftok(".",'u'), 0);

	// declare my message buffer
	struct buf {
		long mtype; // required
		char greeting[50]; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	int r = 200;
	while(r>100){
	r = rand() % ((int) pow(2,32) - 1);
	//For Receiver 1
	msg.mtype = 997; 	
	msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
	cout<<"997 sent to Receiver 1 Number :"<<r<<endl;
	msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0); // reading
	


	//For Receiver 2
	msg.mtype = 997; 	// set message type mtype = 117
	msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
	cout<<"997 sent to Receiver 2 Number :"<<r<<endl;
	msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0); // reading
	}
	cout<<"997 stops"<<endl;
	

	exit(0);
}


