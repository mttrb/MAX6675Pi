#include <stdlib.h>

#include <wiringPi.h>

#include "MAX6675.h"


#define MAX6675_CLOCK_SPEED 4000000

typedef struct MAX6675 {
	int	SPIChannel;
	MAX6675TempScale scale;
} *pMAX6675;

MAX6675 MAX6675Setup(int SPIChannel) {
	if (wiringPiSPISetup(SPIChannel, MAX6675_CLOCK_SPEED) == -1) {
		return 0;
	}
	
	pMAX6675 max6675 = (pMAX6675)malloc(sizeof(struct MAX6675));

	max6675->SPIChannel = SPIChannel;
	max6675->scale = MAX6675_CELCIUS;
	
	return (MAX6675)max6675;
}

void MAX6675Free(MAX6675 handle) {
	if (handle) {
		pMAX6675 max6675 = (pMAX6675)handle;

		free(max6675);	
	}
}

void MAX6675SetScale(MAX6675 handle, MAX6675TempScale scale) {
	if (handle) {
		pMAX6675 max6675 = (pMAX6675)handle;
	
		max6675->scale = scale;
	}
}

MAX6675TempScale MAX6675GetScale(MAX6675 handle) {
	if (handle) {
		pMAX6675 max6675 = (pMAX6675)handle;

		return max6675->scale;
	}

	return MAX6675_CELCIUS;
}

float MAX6675GetTempC(MAX6675 handle) {
	if (handle == 0) { 
		return 0.0f;
	}

	pMAX6675 max6675 = (pMAX6675)handle;

	char buffer[2] = {0, 0};

	int ret = wiringPiSPIDataRW(max6675->SPIChannel, buffer, 2);		

	if (ret != 2) {
		return 0.0f;
	}

	short reading = (buffer[0] << 8) + buffer[1];
	reading >>= 3;

	return reading * 0.25;
}


float MAX6675GetTempK(MAX6675 handle) {
	return MAX6675GetTempC(handle) + 273.15;
}

float MAX6675GetTempF(MAX6675 handle) {
	return (MAX6675GetTempC(handle) * 1.8) + 32.0;
}

float MAX6675GetTemp(MAX6675 handle) {
	if (handle) {
		pMAX6675 max6675 = (pMAX6675)handle;
	
		switch(max6675->scale) {
			case MAX6675_KELVIN:
				return MAX6675GetTempK(handle);

			case MAX6675_FAHRENHEIT:
				return MAX6675GetTempF(handle);
		
			default:
				return MAX6675GetTempC(handle);	
		}
	} else {
		return 0.0f;
	}
}
