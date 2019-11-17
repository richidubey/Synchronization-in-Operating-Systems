#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>

sem_t shopfull;
//Shop full runs contradictory motion, if full, val would be 0, otherwise non zero.
void* barber(void* ptr)
{
	int ret=sem_wait(&shopempty);		//barber waits if shop is empty. Basically he sleeps.
	
	
	
	for(int i=0;i<50;i++)
	printf("This is Barber\n");
	
	
	ret=sem_post(&shopfull);			//Increases value of shop full
	
}


void* customer(void* ptr)
{
	int curr;
	int ret=sem_wait(&shopfull);		//wait if shop is full.
	
		
	for(int i=0;i<50;i++)
	printf("This is customer\n");
	
	ret=sem_post(&shopempty);		//Customer successfully enters, so signals barber to wake up if asleep. Otherwise stay awake until he gets served.	
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
	
	//ret=sem_trywait(&sem);
	
	//Atomically decrements the value of sem, this is non blocking version of sem_wait. So if the value is zero, it does not do anything.
	
	//ret=sem_wait(&sem);
	
	//sem_wait blocks the calling thread until the count in the thread becomes greater than zero, then it automatically decrements it.
	
	
	pthread_t pidc,pidb;
	
	pthread_create(&pidb,NULL,barber,NULL);
	
	pthread_create(&pidc,NULL,customer,NULL);
	
	
	pthread_join(pidb,NULL);	
	pthread_join(pidc,NULL);
	

	return 0;
}
