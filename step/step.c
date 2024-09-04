#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

#define IN1 21
#define IN2 22
#define IN3 23
#define IN4 24

void step_wave(int step)	// 1000 - 0100 - 0010 - 0001 data shift right
{
	switch (step)
	{
		case 0:
			digitalWrite(IN1, 1);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 0);
			break;
		case 1:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 1);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 0);
			break;
		case 2:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 1);
			digitalWrite(IN4, 0);
			break;
		case 3:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 1);
			break;
	}
}

void step_full(int step)	// 1100 - 0110 - 0011 - 1001
{
	switch (step)
	{
		case 0:
			digitalWrite(IN1, 1);
			digitalWrite(IN2, 1);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 0);
			break;
		case 1:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 1);
			digitalWrite(IN3, 1);
			digitalWrite(IN4, 0);
			break;
		case 2:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 1);
			digitalWrite(IN4, 1);
			break;
		case 3:
			digitalWrite(IN1, 1);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 1);
			break;
	}
}

void step_half(int step)	// 1100 - 0100 - 0110 - 0010 - 0011 - 0001 - 1001 - 1000
{
	switch (step)
	{
		case 0:
			digitalWrite(IN1, 1);
			digitalWrite(IN2, 1);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 0);
			break;
		case 1:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 1);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 0);
			break;
		case 2:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 1);
			digitalWrite(IN3, 1);
			digitalWrite(IN4, 0);
			break;
		case 3:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 1);
			digitalWrite(IN4, 0);
			break;
		case 4:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 1);
			digitalWrite(IN4, 1);
			break;
		case 5:
			digitalWrite(IN1, 0);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 1);
			break;
		case 6:
			digitalWrite(IN1, 1);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 1);
			break;
		case 7:
			digitalWrite(IN1, 1);
			digitalWrite(IN2, 0);
			digitalWrite(IN3, 0);
			digitalWrite(IN4, 0);
			break;
	}
}

int steps[] = { 4, 4, 8 };

int main(int n, char *s[])	// step 1 2000 [n : CL의 단어 개수(=3), s : CL의 각 단어(의 포인터)]
{
	/*if (n < 2)	// 옵션을 넣어주지 않았을 때
	{
		printf("Usage : step [step_option(1/2/3] [OP_time(ms)]\n\n");
		return 0;
	}*/
	
	char *qs = getenv("QUERY_STRING");	
	char *qs1 = GetToken(qs, '&', 0);  // mode=11
	char *qs2 = GetToken(qs, '&', 1);  // time=11
	
	char *ms = GetToken(qs, '=', 1);  // value=11
	char *ts = GetToken(qs, '=', 1);  // value=11
	
	int mode = atoi(ms);	// s[1] 옵션이 숫자라는 가정
	int msec = atoi(ts);
	
	
	
	wiringPiSetup();
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	int t1 = millis();
	
	while(1)
	{
		for (int i = 0; i < steps[mode-1]; i++)
		{
			switch(i)
			{
				case 1: step_wave(i); break;
				case 2: step_full(i); break;
				case 3: step_half(i); break;
			}
			delay(5);
		}
		if ((millis() - t1) > msec) break;
	}
	
	return 0;
}

