#include <iostream>
using namespace std;
#include <pthread.h>

// shared circular queue
// empty iff: in_index == out_index
// full iff: in_index+1 == out_index (mod 16)
// insert: q[in++] (mod 16)
// remove: q[out++] (mod 16)
char queue[16];
int in = 0;
int out = 0;

bool done = false;

// generate alphabet into queue
void * writer(void *param)
{
	char letter = 'a';
	while (!done) 
	{
		if((in+1)%16 != out)
		{
			queue[in] = letter;
			in = (in + 1)%16;
			letter++;
			if (letter > 'z') letter = 'a';
		}
	}
	return NULL;
}

// print queue contents 
void * reader(void *param)
{
	while (!done) {
		if(in != out)
		{
			char letter = queue[out];
			cout << letter;
			if (letter == 'z')
				cout << endl;
			out = (out+1)%16;
		}
	}
	return NULL;
}

int main()
{
    // startup 2 worker threads to make things go faster ;-)
    pthread_t writer,reader;
    pthread_create(&writer, NULL, ::writer, NULL);
    pthread_create(&reader, NULL, ::reader, NULL);
    
    // wait
    string dummy;
    cin >> dummy;
    done = true;
}