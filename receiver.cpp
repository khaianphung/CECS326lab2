/* 
Bunly Buth
Khai Phung
Tam Tran
Vincent Vu


filename: receiver1.cpp

This is the first receiver. This receiver's role is to create the queue and receive messages from both sender 257 and sender 997. While receiving messages from those senders, the receiver also sends back an acknowledgement message to them before continuing. The program terminates when both senders terminate. Before terminating, this program removes any remaining messages in the queue and then deletes the queue.

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

	// create the message queue
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

	//initialize buf
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	//condition for staying in the loop
	bool play = true;

	//used for checking if senders have terminated
	bool sender997 = true;
	bool sender251 = true;

	// This while loop receives messages with mtype 111 which are sent from sender 997 and 251
	while (play)
	{		
		//receiving msg
		msgrcv(qid, (struct msgbuf *)&msg, size, 111, 0);

		//checking if this message was from sender 997
		if(msg.needAck == true && sender997 == true) 
		{
			//if sender 997 haven't terminated, display message and send ack msg
			if(msg.terminate == false) 
			{
				cout << "Sender 997: " << msg.greeting << endl;
				strcpy(msg.greeting, "Ack from Receiver 1");
				msg.mtype = 333; 	//mtype for sending ack message
				msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			} 
			//if sender 997 has terminated
			else 
			{
				cout << msg.greeting << endl;
				sender997 = false;
			}
		} 
		////checking if this message was from sender 251
		else if (msg.needAck == false && sender251 == true)
		{
			//if sender 251 has terminated
			if(strcmp(msg.greeting, "Sender 251 terminated") == 0) 
			{
				sender251 = false;
			}
			//if sender 251 hasn't terminated, display message as normal
			else 
			{
				cout << "Sender 251: " << msg.greeting << endl;
			}
		}

		//if both senders are terminated
		if(sender997 == false && sender251 == false)
		{
			play = false;
		
		}
		
		//checking to see if sender 997 and 251 are still active
		cout << "boolSender997: " << sender997 << endl;
		cout << "boolSender251: " << sender251 << endl;  		
	}

	///checking amount of messages in queue
	struct msqid_ds buf;
	int checking = msgctl(qid, IPC_STAT, &buf);
	int count = 0;

	//removing messages in queue until empty
	while(buf.msg_qnum > count) 
	{
		msgrcv(qid,(struct msgbuf * )&msg,size,0,0);
		count++;
	}
	cout << "Message Queue is empty" << endl;
		
	///deleting the queue
	msgctl(qid,IPC_RMID,NULL);
	cout << "Message Queue deleted" << endl;

	//terminating receiver 1
	cout<<"Receiver 1 terminated"<<endl;
	exit(0);
}
