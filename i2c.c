#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main()
{
	int fd = wiringPiI2CSetup(0x48);	// Device 초기
	int v1, v2, v3;
	float f1, f2, f3;
	
	while(1)
	{
		
		wiringPiI2CWrite(fd, 0);	// ch03 (VR) 선택 (가변저항)
		v1 = wiringPiI2CRead(fd);
		f1 = (float)((v1/255.0)*5.0);	// 자동 형변환을 막기 위해 .0 붙이기
		delay(100);
		
		wiringPiI2CWrite(fd, 1);	// ch03 (VR) 선택 (가변저항)
		v2 = wiringPiI2CRead(fd);
		f2 = (float)((v2/255.0)*5.0);	// 자동 형변환을 막기 위해 .0 붙이기
		delay(100);
		
		wiringPiI2CWrite(fd, 3);	// ch03 (VR) 선택 (가변저항)
		v3 = wiringPiI2CRead(fd);
		f3 = (float)((v3/255.0)*5.0);	// 자동 형변환을 막기 위해 .0 붙이기
		printf("ADC input level = %d %d %d (%4.1fV %4.1fV %4.1fV)\n", v1, v2, v3, f1, f2, f3);
		delay(100);
	}
}
