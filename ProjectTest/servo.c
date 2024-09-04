#include <wiringPi.h>
#include <stdio.h>

#define SERVO_PIN 1
#define TRIG 8
#define ECHO 9

extern double Dist();
double d = 0.0;


const int PWM_0_DEGREE = 50;
const int PWM_90_DEGREE = 150;


void setServoPosition(int pwmValue)
{
    pwmWrite(SERVO_PIN, pwmValue);
}

int main(void)
{
    if (wiringPiSetup() == -1)
    {
        printf("wiringPi setting fail\n");
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
	if (d < 30)
	{
	    setServoPosition(PWM_90_DEGREE);
	    delay(7000);
	}
	else
	{
	    setServoPosition(PWM_0_DEGREE);
	    delay(100); 
	}
    }

    return 0;
}
