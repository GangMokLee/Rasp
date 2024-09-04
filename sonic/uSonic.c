#include <stdio.h>
#include <wiringPi.h>

#define TRIG 8
#define ECHO 9

extern double Dist();
double d = 0.0;
int park = 0;

int parking()
{
	if (d < 10)
	{
		park = 1;
	}
	else
	{
		park = 0;
	}
}

int main()
{
	wiringPiSetup();	// 핀 번호 넘버링 메소드 : wPi
	
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	for (;;)
	{
		d = Dist();
		parking();
		if (park)
		{
			printf("차가 주차되어 있습니다. \n");
			delay(500);
		}
		else
		{
			printf("거리 : %.2f(cm) \n", d);	// cm 단위의 거리
			delay(500);
		}
	}
	return 0;
}



