#include <iostream>
#include <queue>
using namespace std;
#include <pthread.h>

queue<int> dataqueue;
string message = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\n";
int index = 0;

// help output the message one character at a time
// the next character to output is at message[index]
void * job(void *param)
{
	int *id = (int *) param; //our process id
	bool queued = false;	  //don't want to blow up the queue (and memory)
	while (true) {
		if(dataqueue.front() == *id)
    	{
			cout << message[index];
    		index++;
    		if (index >= message.length())
        		index = 0;
			//pop out the queue id if it was in there and set our queued flag to false
			if(!dataqueue.empty())
				dataqueue.pop();
			queued = false;
		}
		else if(queued == false) // If we didn't get to act we need to get in line
		{
			dataqueue.push(*id);
			queued = true;
		}		
	}
	return NULL;
}

int main()
{
    // startup 20 worker threads to make things go faster ;-)
	int ids[20];
    pthread_t threads[20];
    for (int i=0; i<20; i++)
    {
		ids[i] = i;
		pthread_create(&threads[i], NULL, job, &ids[i]);
	}
    
    // wait
    string dummy;
    cin >> dummy;
    
    // abandon ship
    exit(0);
}