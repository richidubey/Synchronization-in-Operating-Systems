 #include<semaphore.h>
#include<stdio.h>
#include <stdbool.h>
#include<pthread.h>
#define N 5
#include<sys/syscall.h>		//to get thread id
#include <linux/unistd.h>
#include <unistd.h>

sem_t shopempty;

sem_t mutex;

int cust_count=0;
sem_t mutex,bmutex;
bool shop[N];

int in=0,out=0;
//Shop full runs contradictory motion, if full, val would be 0, otherwise non zero.
void* barber(void* ptr)
{	

	do
	{

	sem_wait(&bmutex);
	
	int ret=sem_wait(&shopempty);		//barber waits if shop is empty. Basically he sleeps.
	
	
	
	printf("This is Barber currently working on its customer %d\n",out);
	out=(out+1)%N;
	
	cust_count--;		//One customer served
	
	sem_post(&bmutex);	
	
	}while(1);	
}


void* customer(void* ptr)
{
	//int curr;
//	int ret=sem_getvalue(&shopfull,&curr);		//Check if shop is full.
											//Allowed as no one is actually waiting on shop full
	if(cust_count==N)
	return NULL;
	
	sem_wait(&mutex);
	
	cust_count++;	
	
	printf("This is customer entering the shop with tid = %ld at pos = %d\n",syscall(__NR_gettid),in);
	
	in=(in+1)%N;
	
	sem_post(&shopempty);		//Customer successfully enters, so signals barber to wake up if asleep. Otherwise stay awake until he gets served.
	
	
	sem_post(&mutex);
		
}


int main()
{
	
	//sem_t sem;
	
	int pshared;
	
	int ret;
	
	int val;
	
	for(int i=0;i<N;i++)
	shop[i]=0;
	
	pshared = 0 ; //private to process
	val =1 ;
	
	//ret=sem_init(&shopfull,pshared,0);
	sem_init(&shopempty,pshared,0);
	
	sem_init(&bmutex,pshared,1);
	sem_init(&mutex,pshared,1);
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
	
	
	//ret=sem_getvalue(&sem,&sval);
	
	
	//places the current value of the semaphore into sval.
	//if one or more processes or threads are blocked waiting to lock the semaphore with sem_wait, sval gets two value either 0(linux) or -ve of count in absolute. 
	 
	pthread_t pidc[10],pidb;
	
	pthread_create(&pidb,NULL,barber,NULL);
	
	
	for(int i=0;i<10;i++)
	pthread_create(&pidc[i],NULL,customer,NULL);
	
	
	pthread_join(pidb,NULL);	
	
		for(int i=0;i<10;i++)
	pthread_join(pidc[i],NULL);
	


	return 0;
}
