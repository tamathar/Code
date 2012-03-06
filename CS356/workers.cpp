//Thomas Scroggins
//Manual Multithreading Synchronization Attempt
//This seems to produce almost perfect results
//slightly slower than what is probably appropriate, but its midnight and I still have OOP HW

//First attempt was a queue that queued threads for data access -WAY to slow, but perfect results
//Second attempt was counting for variable lengths of time depending on ID number to stagger data access, and then a stable amount for spacing - no noticable improvement from original
//Third attempt was simply to single lock the variable with a bool - not much improvement
//Fourth was double locking with 2 bools and spacing - better, but still not good
//Fifth attempt is THIS one. I decided that I/O was probably the slowest operation, so I put the increment in that statement so the 2 would be more cohesiv - seems to work, though slightly slow

#include <iostream>
#include <queue>
using namespace std;
#include <pthread.h>

string message = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\n";
int index = 0;
bool startinguse = false;
bool inuse = false;
// help output the message one character at a time
// the next character to output is at message[index]
void * job(void *param)
{
	int *id = (int *) param; //our process id
	
	while (true) 
	{
		//trying to use a double locking system on the variables to weed out fighting programs (trying to avoid incorrect data grabbing)
		if(!startinguse)
		{
			startinguse = true;
			for(int i = 0; i < *id * 20; i++) //to stagger any processes that might have made it in here simeoultaneously
				int dumb = 0;
				
			if(!inuse)
			{
				//we're using the data, you can't
				inuse = true;
				cout <<  message[index++]; // combining the incrementing with the I/O seems to have done the trick?? - Of course this is paired with double locking
				
				
				if (index >= message.length())
					index = 0;
				//okay, it's all theirs
				inuse = false;
				startinguse = false;
			}
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