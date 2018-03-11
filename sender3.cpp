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
	
	
	int counter = 0;

	// ends loop after receiving 5000 messages
	while(counter < 5000)
	{

		//randomly creating 32 bit values numbers
		int r = rand() % ((int) pow(2,32) - 1);
		msg.mtype = 257; 	
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
		cout<<"257 sent to Receiver 1 Number :"<<r<<endl;
		msgrcv(qid, (struct msgbuf *)&msg, size, 257, 0); // reading

	
		cout<<"Counter: "<<counter<<endl;
		counter++;
	}

	cout<<"Sender 257 terminated"<<endl;
	exit(0);
}


