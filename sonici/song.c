#include <stdio.h>
#include <wiringPi.h>

#define wPi_PWM1 23
int PSC = 19;
int RANGE = 100;
//int DUTY = RANGE / 2;

enum { DO=0, Do, RE, Re, MI, FA, Fa, SL, Sl, LA, La, CI };
int pitch[] = { 262,277,294,311,330,349,370,392,415,440,466,494 };
int range[12];  // Range Register values
int song[] = { SL,SL,LA,LA,SL,SL,MI,SL,SL,MI,MI,RE,
	           SL,SL,LA,LA,SL,SL,MI,SL,MI,RE,MI,DO,-1 };
int rythm[] = { 4,4,4,4,4,4,2,4,4,4,4,1,
            	4,4,4,4,4,4,2,4,4,4,4,1 };
void calcRange() // Calc Range values using Pitch data
{
	for(int i=0;i<12;i++)
	{
		range[i] = 19200000 / (PSC * pitch[i]);// .................
	}
}
double rate = 1;
extern double dist;
void playSound(int um, int rthm)  // um : pitch, rythm
{
	pwmSetClock(PSC);  // Prescaler : ~ 1MHz 
	pwmSetRange(range[um]); // Range
	pwmWrite(wPi_PWM1, range[um]/2); 
	// ....rythm 
	rate = (dist > 100) ? 1.0 : (dist < 50) ? 2.0 : 1.5;
	delay(2000 / (rthm * rate));
	pwmWrite(wPi_PWM1, 0); delay(10);
}
int iFlag = 0;
void initSound()
{
	wiringPiSetup();
	pinMode(wPi_PWM1, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	calcRange();
	iFlag = 1;
}
void PlayEx()
{
	if(!iFlag) initSound(); //  iFlag == 0

	pinMode(wPi_PWM1, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	for(int i=0;song[i]!=-1;i++)
	{
		playSound(song[i], rythm[i]);
	} 
	pwmWrite(wPi_PWM1, 0); 
	pinMode(wPi_PWM1, OUTPUT);
}
void Play(double r)
{
	if(!iFlag) initSound(); //  iFlag == 0
	rate = r;			

	pinMode(wPi_PWM1, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	for(int i=0;song[i]!=-1;i++)
	{
		playSound(song[i], rythm[i]);
	} 
	pwmWrite(wPi_PWM1, 0); 
	pinMode(wPi_PWM1, OUTPUT);
}
/*
int main(int n, char *v[])
{
	double d1 = rate;
	if(n>1)
	{
		 sscanf(v[1], "%lf", &d1);
	} 
	rate = d1;	
	
	wiringPiSetup();
	pinMode(wPi_PWM1, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	calcRange();
	for(int i=0;song[i]!=-1;i++)
	{
		playSound(song[i], rythm[i]);
		//....................
	} 
	pwmWrite(wPi_PWM1, 0); 
	pinMode(wPi_PWM1, OUTPUT);

	return 0;
}*/
