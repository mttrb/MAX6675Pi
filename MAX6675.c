#include <stdlib.h>

#include <wiringPi.h>

#include "MAX6675.h"


#define MAX6675_CLOCK_SPEED 4000000

MAX6675 MAX6675Setup(int SPIChannel) {
	if (wiringPiSPISetup(SPIChannel, MAX6675_CLOCK_SPEED) == -1) {
		return 0;
	}

	MAX6675 max6675 = (MAX6675)malloc(sizeof(struct MAX6675));

	max6675->SPIChannel = SPIChannel;
	max6675->scale = MAX6675_CELSIUS;

	return max6675;
}

void MAX6675Free(MAX6675 max6675) {
	if (max6675) {
		free(max6675);
	}
}

void MAX6675SetScale(MAX6675 max6675, MAX6675TempScale scale) {
	if (max6675) {
		max6675->scale = scale;
	}
}

MAX6675TempScale MAX6675GetScale(MAX6675 max6675) {
	if (max6675) {
		return max6675->scale;
	}

	return MAX6675_CELSIUS;
}

float MAX6675GetTempC(MAX6675 max6675) {
	if (max6675 == 0) {
		return 0.0f;
	}

	char buffer[2] = {0, 0};

	int ret = wiringPiSPIDataRW(max6675->SPIChannel, buffer, 2);

	if (ret != 2) {
		return 0.0f;
	}

	short reading = (buffer[0] << 8) + buffer[1];
	reading >>= 3;

	return reading * 0.25;
}


float MAX6675GetTempK(MAX6675 max6675) {
	return MAX6675GetTempC(max6675) + 273.15;
}

float MAX6675GetTempF(MAX6675 max6675) {
	return (MAX6675GetTempC(max6675) * 1.8) + 32.0;
}

float MAX6675GetTemp(MAX6675 max6675) {
	if (max6675) {
		switch(max6675->scale) {
			case MAX6675_KELVIN:
				return MAX6675GetTempK(max6675);

			case MAX6675_FAHRENHEIT:
				return MAX6675GetTempF(max6675);

			default:
				return MAX6675GetTempC(max6675);
		}
	} else {
		return 0.0f;
	}
}
