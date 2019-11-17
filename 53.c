#include<stdlib.h>
#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>

#define N 5
#define M 3


sem_t rdr;
int readcount=0;

sem_t mutex;
sem_t writergonow;
sem_t wrt;


void* reader(void *ptr)
{
	sem_wait(&rdr);
		
	sem_wait(&mutex);		//to make increasing readcount a CS.
	
	readcount++;
	
	if(readcount==1)
		sem_wait(&wrt);
	
	if(readcount>=3)
	{
		int val;
		sem_getvalue(&wrt,&val);
		
		if(val==0)
		//Some thread is waiting on wrt. Writer thread is waiting on it. So dont allow this to happen. Let the writer go first now.
		{
			sem_wait(writergonow);
			
		}
		
		
	}
	sem_post(&mutex);
	
	
//	printf("Reader %d is reading",atoi(ptr));
		printf("Reader is reading\n");
	
	sem_wait(&mutex);

	readcount--;
	
	if(readcount==0)
		sem_post(&wrt);
	
	sem_post(&mutex);
		
	sem_post(&rdr);
	
}

void* writer(void *ptr)
{
	sem_wait(&wrt);
	
//	printf("Writer %d is writing",atoi(ptr));
		printf("Writer is writing\n");
	
	
	sem_post(&wrt);
}



int main()
{
	
	pthread_t rthread[N];
	
	pthread_t wthread[M];	
	
	sem_init(&rdr,0,5);		//Max 5 readers allowed. 0 - pshared : shared inside process

	sem_init(&mutex,0,1);

	sem_init(&wrt,0,1);
	
	for(int i=0;i<N;i++)
	//pthread_create(&rthread[i],NULL,reader,(int*)(i+1));
	pthread_create(&rthread[i],NULL,reader,NULL);

	for(int i=0;i<M;i++)
//	pthread_create(&wthread[i],NULL,writer,(int*)(i+1));
		pthread_create(&wthread[i],NULL,writer,NULL);
		
		
	for(int i=0;i<N;i++)
	pthread_join(rthread[i],NULL);
	
	for(int i=0;i<M;i++)
	pthread_join(wthread[i],NULL);	

	return 0;
}
