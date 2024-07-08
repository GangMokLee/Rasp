#include <stdio.h>
#include <wiringPi.h>

#define TRIG 8
#define ECHO 9

extern double Dist();

int main()
{
	wiringPiSetup();	// 핀 번호 넘버링 메소드 : wPi
	
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	for (;;)
	{
		
		printf("거리 : %f(cm) \n", Dist());	// cm 단위의 거리
		delay(500);
	}
	return 0;
}



