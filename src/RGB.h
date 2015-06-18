#ifndef LIBSWF_RGB_H
#define LIBSWF_RGB_H


#include <stdint.h>
#include "DataStream.h"

class RGB {
public:
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	RGB();
	RGB(uint8_t red, uint8_t green, uint8_t blue);
	RGB(RGB* r);
	RGB(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_RGB_H
