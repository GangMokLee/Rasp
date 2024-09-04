#include <stdio.h>
#include <wiringPi.h>

#define SERVO_PIN 1	// WPI 1, GPIO 18
#define TRIG 8		// WPI 8, SDA1
#define ECHO 9		// WPI 9, SCL1

const int PWM_0_DEGREE = 50;
const int PWM_90_DEGREE = 150;
double d = 0.0;

void setServoPosition(int pwmValue)
{
    pwmWrite(SERVO_PIN, pwmValue);
}

void Trigger()
{
    digitalWrite(TRIG, 1);
	delayMicroseconds(10);
	digitalWrite(TRIG, 0);
	delayMicroseconds(200);
}

double Dist()
{
    Trigger();
	//while (digitalRead(ECHO) != 0);	// 버스트 시작 기다리기
		
	// 에코 신호 기다리기
	while (digitalRead(ECHO) != 1)
	{
		printf("버스트 시작 기다리기\n");
	}
	int t1 = micros();	// 시작 시간 받아오기 (마이크로초)
	while (digitalRead(ECHO) != 0)
	{
		printf("버스트 신호가 끝날 때까지 기다리기\n");
	}
	int t2 = micros();	// 종료 시간 받아오기
	//double dist = (t2 - t1) * (340 / 1000000 / 2 * 100);
		
	return (t2 - t1) * 0.017;
}

int main(void)
{
    if (wiringPiSetup() == -1) {
        printf("wiringPi 초기화에 실패했습니다.\n");
        return 1;
    }

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(SERVO_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(200);
    pwmSetClock(192);

    while (1)
    {
        d = Dist();
        if (d == -1) {
            printf("거리 측정에 실패했습니다.\n");
        } else if (d < 30) {
            printf("거리가 30cm 미만입니다. 거리 : %.2f cm\n", d);
            setServoPosition(PWM_0_DEGREE);
        } else {
            printf("거리가 30cm 이상입니다. 거리 : %.2f cm\n", d);
            setServoPosition(PWM_90_DEGREE);
        }
        delay(1000);  // 1�� ���
    }
    return 0;
}
