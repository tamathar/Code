#include <iostream>
#include <cassert>
using namespace std;
#include <pthread.h>

// shared variables
const int MAX_X = 7;
const int MAX_Y = 9;
long long matrix[MAX_X*MAX_Y] = {0};
bool done = false;
int done_count = 0;
int reader_count = 0;

//mutexes
pthread_mutex_t mainlock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t readerlock = PTHREAD_MUTEX_INITIALIZER; 

struct Params { // for parameter passing
   int offset;  	// read-only
   int step;    	// read-only
   int count;   	// read-only
   long long iterations;  // writers update this
};

Params what[] = {
   { 0, 1, MAX_X*MAX_Y },   // whole thing
   { 0*MAX_X, 1, MAX_X },   // row 0
   { 1*MAX_X, 1, MAX_X },   // row 1
   { 2*MAX_X, 1, MAX_X },
   { 3*MAX_X, 1, MAX_X },
   { 4*MAX_X, 1, MAX_X },
   { 5*MAX_X, 1, MAX_X },
   { 6*MAX_X, 1, MAX_X },
   { 7*MAX_X, 1, MAX_X },
   { 8*MAX_X, 1, MAX_X },
   { 0, MAX_X, MAX_Y }, 	// col 0
   { 1, MAX_X, MAX_Y }, 	// col 1
   { 2, MAX_X, MAX_Y },
   { 3, MAX_X, MAX_Y },
   { 4, MAX_X, MAX_Y },
   { 5, MAX_X, MAX_Y },
   { 6, MAX_X, MAX_Y }};
const int NUM = sizeof(what)/sizeof(what[0]);

// generate letters into queue
void * writer(void *param)
{
   Params *p = (Params *)param;
   while (!done) {
   	int index = p->offset;
   	for (int i=0; i<p->count; i++) {
       	//begin mutual exclusion
		pthread_mutex_lock(&mainlock);
       	matrix[index]++;
       	// end mutual exclusion
		pthread_mutex_unlock(&mainlock);
       	index += p->step;
   	}
   	p->iterations++;
   }
   done_count++;
   return NULL;
}

// print queue contents
void * reader(void *param)
{
   Params *p = (Params *)param;
   int previous = 0;
   while (!done) {
   	int index = p->offset;
   	int sum = 0;
	
   	// begin mutual exclusion
	pthread_mutex_lock(&readerlock);
	if(reader_count > 0)
	{
		reader_count++;
		pthread_mutex_unlock(&readerlock);
	}
	else
	{
		pthread_mutex_unlock(&readerlock);
		while(pthread_mutex_trylock(&mainlock) != 0 && reader_count <= 0) ;
		pthread_mutex_lock(&readerlock);
		reader_count++;
		pthread_mutex_unlock(&readerlock);
	}

	for (int i=0; i<p->count; i++) {
		sum += matrix[index];
		index += p->step;
	}
	
   	// end mutual exclusion
	pthread_mutex_lock(&readerlock);
	reader_count--;
	if(reader_count <= 0)
		pthread_mutex_unlock(&mainlock);
	pthread_mutex_unlock(&readerlock);
	
	
   	assert(sum >= previous);
   	previous = sum;
   }
   return NULL;
}

int main()
{
   pthread_t writers[NUM];
   pthread_t readers[NUM];
   for (int i=0; i<NUM; i++) {
   	pthread_create(writers+i,NULL,writer,(void *)(what+i));
   	pthread_create(readers+i,NULL,reader,(void *)(what+i));
   }

   // wait
   string dummy;
   cin >> dummy;
   done = true;
   
   while (done_count != NUM)
       ;

   int sum = 0;
   for (int i=0; i<MAX_X*MAX_Y; i++) {
   	int all_incs = what[       	0].iterations;
   	int col_incs = what[10 + i%MAX_X].iterations;
   	int row_incs = what[ 1 + i/MAX_X].iterations;
   	assert(matrix[i] == all_incs + row_incs + col_incs);
   	sum += matrix[i];
   }
   cout << sum << endl;
}