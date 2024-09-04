#include <stdio.h>
#include <wiringPi.h>

#define TRIG 8
#define ECHO 9
#define LED  7

extern double Dist();
double distance = 0.0;

int main()
{
	wiringPiSetup();	// 핀 번호 넘버링 메소드 : wPi
	
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	pinMode(LED, OUTPUT);
	for (;;)
	{
		distance = Dist();
		if (distance <= 30)
		{
			digitalWrite(LED, HIGH);
		}
		else
		{
			digitalWrite(LED, LOW);
		}
		printf("거리 : %.2f(cm) \n", distance);	// cm 단위의 거리
		delay(500);
	}
	return 0;
}



