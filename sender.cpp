/* 
Bunly Buth
Khai Phung
Tam Tran
Vincent Vu

filename: sender.cpp (Sender 997)

This is sender 997. The sender repeatedly sends a random 32 bit value to receivers 1 and 2. Upon sending the value, the sender waits till it receives an acknowledgement message from the each receiver to resume sending messages to both receivers. The program terminates when the generated random 32 bit value is a value less than 100.

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
	bool terminate;		// used to check for termination
	
};

int main() 
{

	//find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	//checking if receiver 1 and 2 are active
	bool receiver1 = true;
	bool receiver2 = true;
	
	//randomly creating 32 bit values numbers
	int r = rand() % ((int) pow(2,32) - 1);		

	// This while loop sends messages to receiver 1 and 2 after it receives ack messages from them
	// This loop ends when randomizing a number less than 100
	while(r >= 100)
	{
		string c = "";
		
		//if receiver 1 is still active
		if (receiver1 == true) 
		{
			//send for receiver 1
			c = to_string(r);				//change char array to string
			strcpy(msg.greeting,c.c_str());			// putting randomized number into the msg
			msg.mtype = 111; 				//change mtype for msg
			msg.needAck = true;				//this ack is needed from receiver
			msg.terminate = false;				// not terminate yet
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending

			//waiting for ack message
			msgrcv(qid, (struct msgbuf *)&msg, size, 333, 0);
			if (msg.terminate == true) 
			{
				receiver1 = false;
			} 
			else 
			{
				cout << msg.greeting << endl;
			}
		}
		
		//if receiver 2 is still active
		if (receiver2 == true) 
		{
			//send for receiver 2
			c = to_string(r);				//change char array to string
			strcpy(msg.greeting,c.c_str()); 		// putting randomized number into the msg
			msg.mtype = 222; 				//change mtype for msg
			msg.needAck = true;				//this ack is needed from receiver
			msg.terminate = false;				// not terminate yet
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); 	// sending IF YOU DONT PUT THIS IT WILL NEVER RUNS
			
			//waiting for ack message
			msgrcv(qid, (struct msgbuf *)&msg, size, 444, 0);
			if (msg.terminate == true) 
			{
				receiver2 = false;
			}
			else 
			{
				cout << msg.greeting << endl;
			}
		}

		//randomly creating 32 bit values numbers
		r = rand() % ((int) pow(2,32) - 1);		

		//display random number
		cout << r << endl;		
	
		//if randomized number is less than 100, send termination notifications to both receivers
		if(r < 100) 
		{
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
	
	//terminating sender 997
	cout<<"Sender 997 terminated"<<endl;
	exit(0);
}



