#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
int customers;	//counts number of customers
sem_t mutex;	//to protect customer int

sem_t barber;	//Barber has to work when customer arrives;
sem_t customer;

#define N 5		//Max number of customers allowed inside a barber shop

void gettinghaircut()
{
	int dur=rand()%5;
	
	sleep(dur);
}
void *customerThread( void *ptr)
{

	sem_wait(&mutex);
		
		if(customers==N)
		{
			sem_post(&mutex);
			printf("Leaving cause the store is already full babe");
			return NULL;
		}
		
		customers++;
		
		printf("Current num of customers = %d",customers);
		fflush(stdout);
		
	sem_post(&mutex);

	//once inside, sit on free chair;
	printf("Customer %d  has come inside",*((int*)ptr));
	
	sem_post(&customer);	//Increase the number of customer: customer signal for barber to wake up	
	
	//sem_post(&barber);//Signal barber to cut my hair.
	
	//sem_wait(&cut_done);	//Wait for hair cut to get done
	gettinghaircut();
	
	
	sem_wait(&barber);	
		
	sem_wait(&mutex);

		customers--; 	//Once hair cut done, decrease the number of customers

	sem_post(&mutex);

}
	



void * barberThread(void *ptr)
{


	do
	{
	sem_wait(&customer);
	sem_post(&barber);
	
	}while(1);
	// Cut Hair
	
//	sem_post(&cut_done);	
}


int main()
{
	srand(time(0));
	sem_init(&mutex,0,1);
	sem_init(&barber,0,0);
	sem_init(&customer,0,0);
	sem_init(&barber,0,0);
	
	pthread_t b,c[10];

	pthread_create(&b,NULL,barberThread,NULL);
	
	int *pass[10];
	for(int i=0;i<10;i++)
	{
		*pass[i]=i+1;
		pthread_create(&c[i],NULL,customerThread,pass[i]);
	}
	
	pthread_join(b,NULL);
	
	return 0;
}
