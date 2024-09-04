#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <string.h>

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

int main(int argc, char **argv)
{
	pthread_t th;
	wiringPiSetup();
	pinMode(ECHO, INPUT);
	
	if ((n > 1) && (strcmp(v[1], "-i") == 0)
	{
		pinMode(TRIG, PWM_OUTPUT);
		TriggerEx();
		wiringPiSetup(ECHO, INT_EDGE_BOTH, usisr);
	}
	else
	{
		pinMode(TRIG, OUTPUT);
		pthread_create&th, NULL, usThread, NULL);
	}
	
	//wiringPiISR(TRIG, INT_EDGE_BOTH, usisr);
	//TriggerEx();
	pthread_create(&th, NULL, usThread, NULL);
	
	while(1)
	{
		printf("Distance : %.2f     \r", dist);
	}
}
