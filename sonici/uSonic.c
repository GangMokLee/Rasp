#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

#define  TRIG  8
#define  ECHO  9

extern double Dist();

double d = 0.0;
int cnt = 0;
int park = 0;

int parking()
{
	if (d < 10) park = 1;
	else park = 0;
}

void * usThread(void *a)
{
	while(1)
	{
		d = Dist();
		delay(100);
	}
}
void * aaa(void * b)
{
	while(1)
	{
		printf(".\n");
		delay(500);
	}
}
int main(int argc, char **argv)
{
	wiringPiSetup(); // Pin numbering method : wPi
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	
	pthread_t threadA, t1;
	//pthread_create(&t1,NULL,aaa,NULL);
	printf("\033[2J\033[10;30H\n");
	pthread_create(&threadA, NULL, usThread, NULL);
	
	for(;;)
	{	
		parking();
		if (park)
		{
			printf("\033[10;30H차가 주차되어 있습니다.   \n");
		}
		else if(!park)
		{
			printf("\033[10;30HDistance : %.2f(cm)   \n", d);//Dist());
			delay(200);
		}
	}
	return 0;
}

