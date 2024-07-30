#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define wPi_Pin 7
int main(int n, char *s[])
{
	if(n<2) 
	{
		printf("usage : pwm2 [duty_rate(%%)] [[period]] \n\n");
		printf("        period = 10 ms if empty\n\n");
		printf("default value : period = 10 ms, DR = 50%%\n\n");
		//return 1;
	}
	int dr = 50, drh, period = 10;
	if(n>1) sscanf(s[1],"%d",&dr);		// 70
	if(n>2)	sscanf(s[2],"%d",&period);	// 10
	drh = (dr * period) / 100;	//   Mark time : 7
	//drl = period - drh;			//  Space time : 3

	wiringPiSetup();  // wPi Pin numbering
	pinMode(wPi_Pin, OUTPUT);
	
	pwmSetMode(PWM_MODE_MS);
	softPwmCreate(wPi_Pin, drh, period);
	//softPwmWrite(wPi_Pin, 70);
	
	delay(5000);
	softPwmStop(wPi_Pin);
	return 0;
}
