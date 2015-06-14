#ifndef LIBSWF_RGB_H
#define LIBSWF_RGB_H


#include <stdint.h>

class RGB {
public:
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	RGB();
	RGB(uint8_t red, uint8_t green, uint8_t blue);
	RGB(RGB& r);
};


#endif //LIBSWF_RGB_H
