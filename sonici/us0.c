#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

#define  TRIG  8
#define  ECHO  9

extern double Dist();
extern void Play(double r);
extern void PlayEx();

double dist = 0.0;
void * usThread(void *a)
{
	while(1)
	{
		dist = Dist();
		delay(100);
	}
}
int main(int argc, char **argv)
{
	wiringPiSetup(); // Pin numbering method : wPi
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	pthread_t threadA, t1;
	printf("\033[2J\033[10;30H\n");
	pthread_create(&threadA, NULL, usThread, NULL);
	
	for(;;)
	{		
		double d = dist;		
		double r;// = (d > 100) ? 1.0 : (d < 50) ? 2.0 : 1.5;
		if(d > 100) 	r = 1.0;
		else if(d < 50) r = 2.0;
		else 			r = 1.5;
		printf("\033[10;30HDistance : %.2f(cm)...(%.1f)\n", d, r);
		PlayEx();
		//Play(r);
		delay(500);
	}
	return 0;
}

