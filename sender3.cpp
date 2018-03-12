/* 

This is sender 257

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
	long mtype; // required
	char greeting[50]; // mesg content
};

int main() 
{
	
	// find exisiting queue
	int qid = msgget(ftok(".",'u'), 0);

	
	buf msg;
	int size = sizeof(msg)-sizeof(long);


	bool play = true;
	while (play)
	{

		//randomly creating 32 bit values numbers
		int r = rand() % ((int) pow(2,32) - 1);
		string c = to_string(r);
		msg.mtype = 257; 	
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
		strcpy(msg.greeting,c.c_str()); // putting randomized number into the msg
		cout<<"257 sent to Receiver 1 Number :"<<r<<endl;

		//this is probably an error
		if (msgrcv(qid, (struct msgbuf *)&msg, size, 113, IPC_NOWAIT) >= 0)
		{
			exit(0);
		}
	
		cout<<"Counter: "<<counter<<endl;
		counter++;
	}

	cout<<"Sender 257 terminated"<<endl;
	exit(0);
}


