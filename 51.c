
#include<semaphore.h>
#include<stdio.h>

sem_t sem;



void* thread1(void* ptr)
{
	int ret=ret=sem_wait(&sem);
	
	for(int i=0;i<100;i++)
	printf("This is thread 1 executing");
	
	
	ret=sem_post(&sem);
	
}


void* thread2(void* ptr)
{
	int ret=sem_wait(&sem);
	
		
	for(int i=0;i<100;i++)
	printf("This is thread 2 executing");
	
	ret=sem_post(&sem);	
}


int main()
{
	
	//sem_t sem;
	
	int pshared;
	
	int ret;
	
	int val;
	
	pshared = 0 ; //private to process
	val =1 ;
	
	ret=sem_init(&sem,pshared,val);
	
	//Ret 0 for successful completion of func.
	//Multiple threads must not initialize same semaphore
	//A semaphore must not be reinitialized while other threads might be using it. 
	
	if(ret!=0)
	printf("Error in intializing");
	
	//ret=sem_post(&sem);
	
	//sem_post automatically increments the semaphore pointed to by sem. When any thread is blocked on semaphore, it gets unblocked.
	
	
	//ret=sem_wait(&sem);
	
	//sem_wait blocks the calling thread until the count in the thread becomes greater than zero, then it automatically decrements it.
	
	
	pthread_t pid;
	
	pthread_attr_t
	

	return 0;
}
