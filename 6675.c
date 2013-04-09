#include <stdlib.h>
#include <stdio.h>

#include "MAX6675.h"

int main(void) {
	MAX6675 max6675 = MAX6675Setup(0);

	MAX6675SetScale(max6675, MAX6675_CELCIUS);

	if (max6675) {
		while(1) {
			printf("%0.2fC\n", MAX6675GetTemp(max6675));

			sleep(1);
		}

		// We never actually get here
		MAX6675Free(max6675);
	}
}
