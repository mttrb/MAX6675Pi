#include <stdlib.h>
#include <stdio.h>

#include "MAX6675.h"

int main(void) {
	MAX6675 max6675 = MAX6675Setup(0);

	if (max6675) {
		while(1) {
			printf("%0.2fC %0.2fK %0.2fF\n", 
				MAX6675GetTempC(max6675),
				MAX6675GetTempK(max6675),
				MAX6675GetTempF(max6675)
			);

			sleep(1);
		}

		// We never actually get here
		MAX6675Free(max6675);
	}
}
