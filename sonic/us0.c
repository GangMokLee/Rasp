#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

#define TRIG 8
#define ECHO 9

extern double Dist();
extern void Play(double r);

int main()
{
	wiringPiSetup();	// 핀 번호 넘버링 메소드 : wPi
	
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	
	for (;;)
	{
		double d = Dist();
		printf("거리 : %.2f(cm) \n", d);	// cm 단위의 거리
		double r = (d > 100) ? 1.0 : (d < 50) ? 2.0 : 1.5;
		Play(r);
		delay(200);
	}
	return 0;
}
