/* 

This is sender 997

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

	
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	int r = 200;
	bool receiver2 = true;


	//sending mtype 9971 for receiver 1
	//mtype 9972 for receiver 2
	int currentMtype = 9972;
	//sending get out of loop when it randomizes a number less than 100
	while(r>100)
	{

		//randomly creating 32 bit values numbers
		r = rand() % ((int) pow(2,32) - 1);
		string c = to_string(r);

		cout << r << endl;

		if(currentMtype == 9972 && receiver2 == true)
		{	
			currentMtype = 9971;
			
			
			//if there isn't a messsage with mtype 1, then send message
			if(msgrcv(qid, (struct msgbuf *)&msg, size, 111, IPC_NOWAIT) < 0)
			{	
				msg.mtype = 9971; 	
				strcpy(msg.greeting,c.c_str()); // putting randomized number into the msg
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
				
				cout << "Sent to Receiver 1" <<  endl;
			}

			msgrcv(qid, (struct msgbuf *)&msg, size, 111, 0);
			cout << msg.greeting << endl;
		}
		else if( receiver2 == false || currentMtype == 9971 )
		{	
			if(strcmp(msg.greeting, "Receiver 2 has terminated") == 0)
			{
				receiver2 = false;	
			}

			currentMtype = 9972;
			
			
			
			//if there isn't a messsage with mtype 222, then send message
			if(msgrcv(qid, (struct msgbuf *)&msg, size, 222, IPC_NOWAIT) < 0)
			{
				msg.mtype = 9972; 	
				strcpy(msg.greeting,c.c_str()); // putting randomized number into the msg
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending

				cout << "Sent to Receiver 1" <<  endl;
			}

			msgrcv(qid, (struct msgbuf *)&msg, size, 222, 0);
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


