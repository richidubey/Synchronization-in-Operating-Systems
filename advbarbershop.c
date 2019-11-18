/* 
Question : 

Our barbershop has three chairs, three barbers, and a waiting
area that can accommodate four customers on a sofa and that has
standing room for additional customers. Fire codes limit the total
number of customers in the shop to 20.
A customer will not enter the shop if it is filled to capacity with
other customers. Once inside, the customer takes a seat on the sofa
or stands if the sofa is filled. When a barber is free, the customer
that has been on the sofa the longest is served and, if there are any
standing customers, the one that has been in the shop the longest
takes a seat on the sofa. When a customer’s haircut is finished,
any barber can accept payment, but because there is only one cash
register, payment is accepted for one customer at a time. The bar-
bers divide their time among cutting hair, accepting payment, and
sleeping in their chair waiting for a customer.

*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int customers;	//counts number of customers
sem_t mutex;	//to protect customer int

sem_t barber;	//Barber has to work when customer arrives;
sem_t customer;


#define N 5		//Max number of customers allowed inside a barber shop

void *customerThread( void *ptr)
{
	sem_wait(&mutex);
		
		if(customers>=20)
		{
			sem_post(&mutex);
			printf("Leaving cause the store is already full babe,no place even in standing room");
			return NULL;
		}
		
		customers++;

	sem_post(&mutex);
	
	sem_post(&customer);	//Increase the number of customer: customer signal for barber to wake up	
	
	sem_wait(&sofa);	//Wait to sit on sofa
	
	
	sem_wait(&barber);	//Waits for the barber to finish
	
	sem_post(&sofa);	//Once barber finishes, leave sofa and give others a chance to sit on sofa
	
	//Get a haircut.
	
	
	sem_post(&pay);
	//Pay
	sem_wait(&receipt);	//Wait to get your receipt
	
		
	sem_wait(&mutex);

		customers--; 	//Once hair cut done, decrease the number of customers

	sem_post(&mutex);
	
	//Exit shop

}
	



void * barberThread(void *ptr)
{

	sem_wait(&customer);
	
	sem_post(&barber);		//Kind of saying we accept a customer. As a customer must be waiting for a barber
	
	// Cut Hair
	
	sem_wait(&pay);	//Wait for him to pay
	
	//Accept Payment
	
	sem_post(&receipt);
	
//	sem_post(&cut_done);	
}


int main()
{
	sem_init(&mutex,0,1);
	sem_init(&barber,0,0);
	sem_init(&customer,0,0);
	sem_init(&barber,0,0);
	return 0;
}

