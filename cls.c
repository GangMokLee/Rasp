#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main()
{
	printf("\033[2J");	// 화면 클리어
	//printf("\033[1;1H");	// [x;yH
	
	int fd = wiringPiI2CSetup(0x48);
	
	int v1, v2;
	int f1, f2;
	
	while(1)
	{
		
		wiringPiI2CWrite(fd, 0);
		v1 = wiringPiI2CRead(fd);
		f1 = (v1/255.0)*24;
		
		wiringPiI2CWrite(fd, 1);
		v2 = wiringPiI2CRead(fd);
		f2 = (v2/255.0)*80;
		
		printf("\033[%d;%dH*", f1, f2);
	}
	return 0;
}
