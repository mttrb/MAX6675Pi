#ifndef MAX6675_H
#define MAX6675_H

typedef enum {
	MAX6675_CELSIUS,
	MAX6675_KELVIN,
	MAX6675_FAHRENHEIT
} MAX6675TempScale;


typedef struct MAX6675 {
	int	SPIChannel;
	MAX6675TempScale scale;
} *MAX6675;


MAX6675 MAX6675Setup(int SPIChannel);
void MAX6675Free(MAX6675 handle);

void MAX6675SetScale(MAX6675 handle, MAX6675TempScale scale);
MAX6675TempScale MAX6675GetScale(MAX6675 handle);

float MAX6675GetTempC(MAX6675 handle);
float MAX6675GetTempK(MAX6675 handle);
float MAX6675GetTempF(MAX6675 handle);

float MAX6675GetTemp(MAX6675 handle);

#endif
