#include <stdio.h>
#include <wiringPi.h>

#define wPi_PWM1 23

extern double Dist();

int PSC = 19;
int RANGE = 100;
//int DUTY = RANGE / 2;

enum { DO, Do, RE, Re, MI, FA, Fa, SL, Sl, LA, La, CI};
int pitch[] = { 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 };
int range[12];
int song[] = { SL, SL, LA, LA, SL, SL, MI, SL, SL, MI, MI, RE,
			   SL, SL, LA, LA, SL, SL, MI, SL, MI, RE, MI, DO, -1 };
int rhythm[] = { 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 1,
				 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 1 };

void calcRange()	// Range 값 계산 및 음계 데이터 사용
{
	for (int i = 0; i < 12; i++)
	{
		range[i] = 19200000 / (PSC * pitch[i]);
	}
}

double rate = 1;
void playSound(int um, int rhy, double dis)	// um : pitch, rhy : rhythm
{
	pwmSetClock(PSC);	// 프리스케일러 : ~1MHz
	// 10K = 19.2M / (19 * 100)
	pwmSetRange(range[um]);
	pwmWrite(wPi_PWM1, range[um] / 2);
	
	if (dis > 100)
	{
		delay(2000 / rhy);
	}
	else if (dis > 50)
	{
		delay(1000 / rhy);
	}
	else
	{
		delay(500 / rhy);
	}
	
}

int main(int n, char *v[])
{
	double d1 = rate;
	if (n > 1) sscanf(v[1], "%lf", &d1);
	rate = d1;
	wiringPiSetup();
	
	pinMode(wPi_PWM1, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	
	calcRange();
	
	for (int i = 0; song[i] != -1; i++)
	{
		double dis = Dist();
		playSound(song[i], rhythm[i], dis);
	}
	pinMode(wPi_PWM1, OUTPUT); // 하드웨어 PWM은 따로 종료 코드가 없으므로 핀 모드를 바꿔줌
	
	return 0;
}
