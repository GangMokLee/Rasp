#include <stdio.h>
#include <wiringPi.h>

#define  TRIG  8
#define  ECHO  9

double Dist()
{
	// Trigger signal
	digitalWrite(TRIG, 1);
	delayMicroseconds(10);
	digitalWrite(TRIG, 0);	
	delayMicroseconds(210);
	
	//while(digitalRead(ECHO) != 0);	// Wait for burst Start 
	
	// Wait for Echo signal
	while(digitalRead(ECHO) != 1);	// Wait for Echo HIGH 
	//while(1)
	//{
	//	int v = digitalRead(ECHO);
	//	if(v == 0) break;
	//}
	int t1 = micros();  // Get start time (in micro-second)
	while(digitalRead(ECHO) != 0);	// Wait for Echo Low 
	int t2 = micros();	// Get end time
	//double dist = (t2 - t1) * (340 / 1000000 / 2 * 100);
	return (t2 - t1) * 0.017;
}

int main(int argc, char **argv)
{
	wiringPiSetup(); // Pin numbering method : wPi
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	
	for(;;)
	{		
		printf("Distance : %.2f(cm)\n", Dist());
		delay(500);
	}
	return 0;
}
