#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>	//For random numbers
#include<time.h>	//To seed with current time
#include<stdbool.h>	//For bool

sem_t agentsem;
sem_t match;
sem_t paper;
sem_t tobacco;
sem_t mutex;

bool isPaper=false,isTobacco=false,isMatch=false;

sem_t sem_P,sem_T,sem_M;

void *agentA(void *ptr)
{
	sem_wait(&agentsem);
	
	sem_post(&match);
	sem_post(&tobacco);
	
}

void* agentB(void *ptr)
{
	sem_wait(&agentsem);
	
	sem_post(&tobacco);
	sem_post(&paper);
	
}

void* agentC(void *ptr)
{
	sem_wait(&agentsem);
	
	sem_post(&match);
	sem_post(&paper);
	
}

void* pusherA(void *ptr)
{
	sem_wait(&tobacco);
	
	sem_wait(&mutex);
	
	if(isPaper)
	{
		isPaper=false;
		sem_post(&sem_M);
	}
	
	else if(isMatch)
	{
		isMatch=false;
		sem_post(&sem_P);
	}
	
	else
	{
		isTobacco=true;
	}
	
	sem_post(&mutex);
}



void* pusherB(void *ptr)
{
	sem_wait(&paper);
	
	sem_wait(&mutex);
	
	if(isTobacco)
	{
		isTobacco=false;
		sem_post(&sem_M);
	}
	
	else if(isMatch)
	{
		isMatch=false;
		sem_post(&sem_T);
	}
	
	else
	{
		isPaper=true;
	}
	
	sem_post(&mutex);
}



void* pusherC(void *ptr)
{
	sem_wait(&match);
	
	sem_wait(&mutex);
	
	if(isPaper)
	{
		isPaper=false;
		sem_post(&sem_T);
	}
	
	else if(isTobacco)
	{
		isTobacco=false;
		sem_post(&sem_P);
	}
	
	else
	{
		isMatch=true;
	}
	
	sem_post(&mutex);
}



void* smokerwithT(void* ptr)
{
	sem_wait(&sem_T);
	//Make Cigarette;
	sem_post(&agentsem);
	//Smoke your cigarette	
}

void* smokerwithP(void* ptr)
{
	sem_wait(&sem_P);
	//Make Cigarette;
	sem_post(&agentsem);
	//Smoke your cigarette	
}

void* smokerwithM(void* ptr)
{
	sem_wait(&sem_M);
	//Make Cigarette;
	sem_post(&agentsem);
	//Smoke your cigarette	
}

int main()
{

	srand(time(0));
	sem_init(&agentsem,0,1);
	sem_init(&match,0,0);
	sem_init(&paper,0,0);
	sem_init(&tobacco,0,0);
	
	sem_init(&mutex,0,1);
	
	sem_init(&sem_T,0,0);
	sem_init(&sem_P,0,0);
	sem_init(&sem_M,0,0);
	
}
