#include <stdio.h>
#include <wiringPi.h>

#define TRIG 8
#define ECHO 9

double Dist()
{
	// 트리거 신호
		digitalWrite(TRIG, 1);
		delayMicroseconds(10);
		digitalWrite(TRIG, 0);
		delayMicroseconds(200);
		
		//while (digitalRead(ECHO) != 0);	// 버스트 시작 기다리기
		
		// 에코 신호 기다리기
		while (digitalRead(ECHO) != 1);	// 버스트 시작 기다리기
		int t1 = micros();	// 시작 시간 받아오기 (마이크로초)
		while (digitalRead(ECHO) != 0); // 버스트 신호가 끝날 때까지
		int t2 = micros();	// 종료 시간 받아오기
		//double dist = (t2 - t1) * (340 / 1000000 / 2 * 100);
		
		return (t2 - t1) * 0.017;
}

