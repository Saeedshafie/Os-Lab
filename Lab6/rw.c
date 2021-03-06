#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


typedef struct {
	int count , rc;
	sem_t mutex;
	sem_t data;
} SharedData;

int root_pid;
int id;

void writer();
void reader();

int main()
{
	SharedData* sharedData;
	int pid;
	
	id = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | 0666);
	
	sharedData = (SharedData *)shmat(id , NULL , 0);
	
	
	root_pid = getpid();
	
	sem_init(&(sharedData->mutex), 1, 1);
	sem_init(&(sharedData->data), 1,1);
	sharedData->count = 0;
	sharedData->rc = 0;
	
	pid = fork();
	
	// Writer Process
	if( pid == 0) {
		writer();
		return 0;
	}
	
	for( int i = 0;i < 5; i++)
	{
		if(getpid() == root_pid)
		{
			pid = fork();
		}
		else{
			break;
		}
	}
		
	//Reader Process		
	if( pid == 0) {
		reader();
		return 0;
	}
	if (getpid() == root_pid)
	{
		wait(NULL); // Wait for Writer
		for( int i = 0;i < 5; i++) // Wait for Readers
		{
			wait(NULL);
		}
	}
	
	return 0;

}

void reader() { 
	SharedData* sharedData;
	sharedData = (SharedData *)shmat(id, NULL, 0);
	
	int pid = getpid();
	
	bool done = 0;
	while(!done){
		sem_wait((&sharedData->mutex));
		sharedData->rc = sharedData->rc + 1;
		if ( sharedData->rc == 1) {
			sem_wait((&sharedData->data));
		}
		sem_post((&sharedData->mutex));
		printf("Reader : PID = %d , count = %d\n", pid , sharedData->count);
		if( sharedData->count >= 5)
		{
			done = 1;
		}
		sem_wait((&sharedData->mutex));
		sharedData->rc = sharedData->rc - 1;
		if(sharedData->rc == 0) 
		{
			sem_post((&sharedData->data));
		}
		sem_post((&sharedData->mutex));
		
	}
}

void writer()
{
	SharedData* sharedData;
	sharedData = (SharedData *)shmat(id, NULL, 0);
	
	int pid = getpid();
	
	bool done = 0;
	while(!done){
		sem_wait((&sharedData->data));
		sharedData->count++;
		if ( sharedData->count >= 5)
		{
			done = 1;
		}
		printf("Writer : PID = %d , count = %d\n", pid , sharedData->count);
		sem_post((&sharedData->data));
	}
}
