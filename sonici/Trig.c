#include <stdio.h>
#include <wiringPi.h>

#define  TRIG  8
#define  ECHO  9

#define	CLK		19200000
#define PSC		19
#define RANGE	66666   // 15Hz
#define	VAL		10

void TriggerEx()
{
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(PSC*2);
	pwmSetRange(RANGE/2);  // 
	pwmWrite(TRIG, VAL/2);
}

void Trigger()
{
	//wiringPiSetup();
	digitalWrite(TRIG, 1);
	delayMicroseconds(10);
	digitalWrite(TRIG, 0);
	delayMicroseconds(200);  // delay for burst	
}

