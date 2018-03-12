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

	// get out of loop when it randomizes a number less than 100
	while(r>100)
	{

		//randomly creating 32 bit values numbers
		r = rand() % ((int) pow(2,32) - 1);
		string c = to_string(r);


		//For Receiver 1
		msg.mtype = 997; 	
		strcpy(msg.greeting,c.c_str()); // putting randomized number into the msg
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
	
	
		msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0); // reading
		cout<<msg.greeting<<endl;

	}

	cout<<"Sender 997 terminated"<<endl;
	

	exit(0);
}


