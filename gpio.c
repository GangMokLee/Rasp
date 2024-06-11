#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define RED 8
#define YELLOW 9
#define GREEN 7
#define SW 2
#define SW2 3

int ps[40];		// 핀 넘버 40개. 핀 상태 저장, 기본값은 0
int mode = 0;
int intv = 0;	// 0~8
int tim;		// delay time interval
int flag = 1;

void Toggle(int pin)
{
	ps[pin] = !ps[pin];
	digitalWrite(pin,ps[pin]);
}

void gpioisr()
{
	//mode = !mode;
	if (++intv > 8) intv = 0;
	printf("GPIO interrupt occured...\n");
}

void exitisr()
{
	flag = 0;	// while문 종료
	// 모든 LED 끄기
	digitalWrite(RED, 0);
	digitalWrite(YELLOW, 0);
	digitalWrite(GREEN, 0);
	printf("EXIT 인터럽트 발생\n");
}

int main()
{
	wiringPiSetup();	// 핀 번호 사용 설정 (wPi)
	pinMode(RED, OUTPUT);	// 8, 9, 7 : OUT	2 : IN
	pinMode(YELLOW, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(SW, INPUT);
	pinMode(SW2, INPUT);
	wiringPiISR(SW, INT_EDGE_FALLING, gpioisr);	// registration GPIO ISR
	wiringPiISR(SW2, INT_EDGE_FALLING, exitisr);
	

	
	while(flag)
	{
		tim = (9-intv)*100;
		if(mode)
		{
			Toggle(RED);	delay(tim);
			Toggle(YELLOW);	delay(tim);
			Toggle(GREEN);	delay(tim);
		}
		else
		{
			Toggle(RED);	delay(tim);
			Toggle(YELLOW);	delay(tim);
			Toggle(GREEN);	delay(tim);
		}
	}
}
