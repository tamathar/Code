#include <iostream>
#include <queue>
using namespace std;
#include <pthread.h>

string message = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\n";
int index = 0;

// help output the message one character at a time
// the next character to output is at message[index]
void * job(void *param)
{
	int *id = (int *) param; //our process id
	
	//the idea is to stagger when each process grabs for memory
	for(int i = 0; i < *id * 2; i++)
		int useless = i;
		
	while (true) 
	{
		cout << message[index] << "<-" << *id << "--";
    	index++;
    	if (index >= message.length())
        	index = 0;	

		for(int i = 0; i < 2; i ++)
			int useless = i;
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