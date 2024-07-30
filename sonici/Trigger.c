#include <stdio.h>
#include <wiringPi.h>

#define  TRIG  1
#define  ECHO  9

#define	CLK		19200000
#define PSC		19
#define RANGE	1024   // 15Hz
#define	VAL		10

void main()
{
	wiringPiSetup();
	pinMode(TRIG, OUTPUT);
	while(1)
	{
		digitalWrite(TRIG, 1);
		delayMicroseconds(10);
		digitalWrite(TRIG, 0);
		delay(70);
	}
}
