#include <iostream>
#include <cassert>
using namespace std;
#include <pthread.h>

// shared circular queue
// empty iff: in_index == out_index
// full iff: in_index+1 == out_index (mod 16)
// insert: q[in++] (mod 16)
// remove: q[out++] (mod 16)
char queue[16];
int in_index = 0;
int out_index = 0;

// synchronized stopping;
int num_writers = 26;
bool stop_writing = false;
bool writing_stopped[26] = {0};
bool reading_stopped = false;

// debugging / verification variables
int write_counts[26] = {0};
int read_counts[26] = {0};

// queing vars
int numbers[26]= {0};
bool queuing[26] = {false};

//Locking function
void lock(int i)
{
	//tell ppl we're getting in line
	queuing[i] = true;
	//get next number
	int max = 0;
	for(int j = 0; j < num_writers; j++)
		if(numbers[j] > max)
			max = numbers[j];
	numbers[i] = max+1;
	//now ppl can tell we want in so we don't need to shout it
	queuing[i] = false;
	
	for(int j = 0; j < num_writers; j++)
	{	
		//we'll wait for you to get in line
		while(queuing[j]) ;
		//and if you want in a beat us we'll let you go
		while(numbers[j] != 0 && (numbers[j] < numbers[i] || (numbers[j] == numbers[i] && j < i))) ;
		//now its our turn. We're locked!!
	}
	
}

//unlocking function
void unlock(int i)
{
	//we're done, others can go for it
	numbers[i] = 0;
}

// generate letters into queue
void * writer(void *param)
{
	char letter = *(char *)param;
	while (!stop_writing) {
			lock(letter - 'a');
    		if ((in_index+1)%16 != out_index) {
        		queue[in_index] = letter;
        		in_index = (in_index+1) % 16;
        		write_counts[letter-'a']++;
    		}
			unlock(letter - 'a');
	}
	writing_stopped[letter-'a'] = true;
	return NULL;
}

// print queue contents
void * reader(void *param)
{
	while (true) {
    		if (out_index != in_index) {
        		char letter = queue[out_index];
        		read_counts[letter-'a']++;
        		out_index = (out_index+1)%16;
    		}
    		else if (stop_writing) {
        		bool all_done = true;
        		for (int i=0; i<num_writers && all_done; i++)
            		all_done = writing_stopped[i];
        		if (all_done) break;
    		}
	}
	reading_stopped = true;
	return NULL;
}

int main()
{
	char alpha[] = "abcdefghijklmnopqrstuvwxyz";
	pthread_t writers[26];
	pthread_t reader;
	for (int i=0; i<num_writers; i++)
    		pthread_create(writers+i,NULL,writer,(void *)(alpha+i));
	pthread_create(&reader, NULL, ::reader, NULL);
  	 
	// wait
	string dummy;
	cin >> dummy;
	stop_writing = true;
    
	while (!reading_stopped)
    		;
    
	for (int i=0; i<num_writers; i++) {
    		cout << (char)('a'+i) << "\t";
    		cout << write_counts[i] << "\t";
    		cout << read_counts[i] << "\n";
	}
}