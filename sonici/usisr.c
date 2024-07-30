
#include <stdio.h>
#include <wiringPi.h>

#define  TRIG	8
#define  ECHO	9

extern void Trigger();

int t1;
double dist;
void usisr()   // ISR : no arg no return
{
	int tt = micros();
	int sg = digitalRead(ECHO);
	if(sg == 1) t1 = tt;   // Rising Edge : start counter
	else
	{
		dist = (tt - t1) * 0.017;//(340 / 1000000 / 2 * 100);
	}	
}

double Dist()
{
	//wiringPiSetup();
	// Trigger signal
	Trigger();	
	//while(digitalRead(ECHO) != 0);	// Wait for burst Start 
	
	// Wait for Echo signal
	while(digitalRead(ECHO) != 1);	// Wait for Echo HIGH 
	int t1 = micros();  // Get start time (in micro-second)
	while(digitalRead(ECHO) != 0);	// Wait for Echo Low 
	int t2 = micros();	// Get end time
	dist = (t2 - t1) * 0.017;//(340 / 1000000 / 2 * 100);
	return dist;//(t2 - t1) * 0.017;
}
