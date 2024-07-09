#include <stdio.h>
#include <wiringPi.h>

#define SERVO_PIN 1	// wPi number (physical 12)

int main(int argc, char **argv)
{
	wiringPiSetup();
	pinMode(SERVO_PIN, OUTPUT);
	for (int i = 0; i < 5 ; i++)
	{
		for (int i = 0; i < 25 ; i++)
		{
			digitalWrite(SERVO_PIN, 1);
			delayMicroseconds(1000);	// 펄스의 폭은 1ms
			digitalWrite(SERVO_PIN, 0);
			delayMicroseconds(19000);	// 주기는 20ms
		}
		for (int i = 0; i < 25 ; i++)
		{
			digitalWrite(SERVO_PIN, 1);
			delayMicroseconds(1500);
			digitalWrite(SERVO_PIN, 0);
			delayMicroseconds(18500);
		}
		for (int i = 0; i < 25 ; i++)
		{
			digitalWrite(SERVO_PIN, 1);
			delayMicroseconds(2000);
			digitalWrite(SERVO_PIN, 0);
			delayMicroseconds(18000);
		}
		for (int i = 0; i < 25 ; i++)
		{
			digitalWrite(SERVO_PIN, 1);
			delayMicroseconds(1500);
			digitalWrite(SERVO_PIN, 0);
			delayMicroseconds(18500);
		}
	}
	for (int i = 0; i < 25 ; i++)
	{
		digitalWrite(SERVO_PIN, 1);
		delayMicroseconds(1000);	// 펄스의 폭은 1ms
		digitalWrite(SERVO_PIN, 0);
		delayMicroseconds(19000);	// 주기는 20ms
	}
	
	return 0;
}

