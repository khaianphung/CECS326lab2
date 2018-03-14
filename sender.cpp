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
	long mtype; // required
	char greeting[50]; // mesg content
};

int main() 
{

	//find existing queue
	int qid = msgget(ftok(".",'u'), 0);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	//r: variable to hold the random 32 bit value
	//Initially 200 to start the loop
	//receiver2: variable that keeps track of receiver2 termination
	int r = 200;
	bool receiver2 = true;


	//sending mtype 9971 for receiver 1
	//sending mtype 9972 for receiver 2
	int currentMtype = 9972;

	//get out of loop when it randomizes a number less than 100
	while(r>100)
	{
		r = rand() % ((int) pow(2,32) - 1);		//randomly creating 32 bit values numbers
		string c = to_string(r);			//change char array to string

		cout << r << endl;				//display random number
		
		//Precondition: if receiver2 is still active
		if(currentMtype == 9972 && receiver2 == true)	//swapping mtypes
		{	
			currentMtype = 9971;			//change mytypes for conditional
			
			//if there isn't a messsage with mtype 1, then send message
			if(msgrcv(qid, (struct msgbuf *)&msg, size, 111, IPC_NOWAIT) < 0)
			{	
				msg.mtype = 9971; 		//change mtype for msg
				strcpy(msg.greeting,c.c_str()); // putting randomized number into the msg
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
				
				cout << "Sent to Receiver 1" <<  endl;
			}

			msgrcv(qid, (struct msgbuf *)&msg, size, 111, 0);	//wait to receive acknowledge message from receiver 1
			cout << msg.greeting << endl;
		}
		else if(receiver2 == false || currentMtype == 9971 )	//swapping mtypes if receiver2 terminated or if its receiver1's turn
		{	
			if(strcmp(msg.greeting, "Receiver 2 has terminated") == 0)	//check to see if receiver 2 has terminated
			{
				receiver2 = false;	
			}

			currentMtype = 9972;			//change mytypes for conditional
			
		
			//if there isn't a messsage with mtype 222, then send message
			if(msgrcv(qid, (struct msgbuf *)&msg, size, 222, IPC_NOWAIT) < 0)
			{
				msg.mtype = 9972; 		//change mtype for msg
				strcpy(msg.greeting,c.c_str()); // putting randomized number into the msg
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending

				cout << "Sent to Receiver 1" <<  endl;
			}

			msgrcv(qid, (struct msgbuf *)&msg, size, 222, 0);	//wait to receive acknowledge message from receiver 2
			cout << msg.greeting << endl;
		}

	}

	//sending last message to receiver 1
	msg.mtype = 997; 	
	strcpy(msg.greeting,"Sender 997 terminated"); // putting randomized number into the msg
	msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
	cout<<"Sender 997 terminated"<<endl;
	

	exit(0);
}


