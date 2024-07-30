#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

#define  TRIG  8
#define  ECHO  9

extern double Dist();
extern void Play(double r);
extern void PlayEx();

double dist = 0.0;
int t1=0;

void usISR()
{
	int tt = micros();
	int s1 = digitalRead(ECHO);
	if(s1 == 1) t1 = tt;
	else
	{
		dist = (tt - t1) * 0.017;
	}
}
int main(int argc, char **argv)
{
	wiringPiSetup(); // Pin numbering method : wPi
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	wiringPiISR(ECHO, INT_EDGE_BOTH, usISR);  // registration ECHO ISR 
	printf("\033[2J\033[10;30H\n");

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

