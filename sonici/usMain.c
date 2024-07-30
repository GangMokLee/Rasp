#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

#define TRIG 8
#define ECHO 9

extern void TriggerEx();
extern void usisr();
extern double Dist();
extern double dist;

void *usThread(void *a)
{
	while(1)
	{
		Dist(); delay(70);
	}
}

int main()
{
	pthread_t th;
	wiringPiSetup();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	
	//wiringPiISR(TRIG, INT_EDGE_BOTH, usisr);
	//TriggerEx();
	pthread_create(&th, NULL, usThread, NULL);
	
	while(1)
	{
		printf("Distance : %.2f     \r", dist);
	}
}
