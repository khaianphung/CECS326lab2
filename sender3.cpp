/* 
Tam Tran
Khai Phung
Vincent Vu
Bunly Buth

filename: sender3.cpp (sender 257)
This is sender 257. Sender 257 repeatedly sends a random 32 bit value to receiver 2.
Sender 257 terminates when receiver 2 terminates.

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

// declare my message buffer
struct buf 
{
	long mtype; 		// required identifier
	char greeting[50]; 	// mesg content
	bool needAck;		// to know if receiver needs to send an ack msg to sender 997
	bool terminate;		//used to check for termination

};

int main() 
{
	
	// find existing queue
	int qid = fork();//msgget(ftok(".",'u'), 0);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	
	msg.mtype = 111;
	strcpy(msg.greeting,"Sender 257 terminated");
	msg.needAck = false;				// this sender does not need ack messages
	msg.terminate = true;
	


	bool play = true;
	while(play)
	{
		int r = rand() % ((int) pow(2,32) - 1);		// randomly creating 32 bit values numbers
		string c = to_string(r);			// change char array to string
		msg.mtype = 111; 				// changing mtype to send to receiver 1
		msg.needAck = false;				// this sender does not need ack messages		
		msg.terminate = false;				// not terminate yet
		strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg

		msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending
		
		cout << r << endl;		// display random number
	}
	
	cout<<"Sender 257 terminated"<<endl;
	exit(0);
	
}

