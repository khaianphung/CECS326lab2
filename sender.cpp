/* 
Tam Tran
Khai Phung
Vincent Vu
Bunly Buth

filename: sender.cpp (Sender 997)
This is sender 997. The sender repeatedly sends a random 32 bit value to receivers 1 
and 2. Upon sending the value, the sender waits till it receives an acknowledgement 
message from the receiver to resume. The program terminates when the generated random 
32 bit value is a value less than 100.

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
#include <string>
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

	//find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	//sending mtype 111 for receiver 1
	//sending mtype 222 for receiver 2
	//mtype 333 for acknowledgement


	//sending first pair of messages
	int r = rand() % ((int) pow(2,32) - 1);		//randomly creating 32 bit values numbers

	//cout << r << endl;		//display random number


	//get out of loop when it randomizes a number less than 100
	while(r >= 100)
	{
		//send for receiver 1
		string c = to_string(r);			//change char array to string
		strcpy(msg.greeting,c.c_str());
 
		msg.mtype = 111; 				//change mtype for msg
		msg.needAck = true;				//this ack is needed from receiver
		msg.terminate = false;				// not terminate yet
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending

		msgrcv(qid, (struct msgbuf *)&msg, size, 333, 0);
		cout << msg.greeting << endl;
		
		//send for receiver 2
		c = to_string(r);			//change char array to string
		strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg
		msg.mtype = 222; 				//change mtype for msg
		msg.needAck = true;				//this ack is needed from receiver
		msg.terminate = false;				// not terminate yet
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending IF YOU DONT PUT THIS IT WILL NEVER RUNS
		msgrcv(qid, (struct msgbuf *)&msg, size, 444, 0);
		cout << msg.greeting << endl;
		
		r = rand() % ((int) pow(2,32) - 1);		//randomly creating 32 bit values numbers

		cout << r << endl;		//display random number

		if(r < 100) {
			strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg
			msg.mtype = 111;
			msg.needAck = true;				//this ack is needed from receiver
			msg.terminate = true;				// terminate
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending
	
			strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg
			msg.mtype = 222;
			msg.needAck = true;				//this ack is needed from receiver
			msg.terminate = true;				// terminate
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending
		}
		

	}
	
	//termination of this program
	cout<<"Sender 997 terminated"<<endl;
	exit(0);
}


