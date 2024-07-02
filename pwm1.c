#include <stdio.h>
#include <wiringPi.h>

#define wPi_22 22

int main(int n, char * s[])
{
	int dr, drh, drl, period = 10;
	
	if (n<2)
	{
		printf("usage : pwm1 [duty_rate(%%)] [period]\n\n");
		printf("		period = 10 ms if empty\n\n");
		return 1;
	}
	else
	{
		sscanf(s[1],"%d",&dr);
		
		if (n > 2) sscanf(s[2], "%d", &period);
	}
	
	
	drh = (dr * period) / 100;	// 7
	drl = period - drh;			// 3
	
	wiringPiSetup();	// wPi 핀 넘버링
	
	pinMode(wPi_22, OUTPUT);
	for (int i = 0; i < 100; i++)
	{
		digitalWrite(wPi_22, 1);
		delay(drh);
		digitalWrite(wPi_22, 0);
		delay(drl);
	}
	
	return 0;
}
