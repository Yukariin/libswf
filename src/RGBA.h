#ifndef LIBSWF_RGBA_H
#define LIBSWF_RGBA_H


#include "RGB.h"

class RGBA : public RGB {
public:
	int alpha;

	RGBA(DataStream* ds);
	RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	RGBA(RGBA* r);

	void readData(DataStream* ds);
};


#endif //LIBSWF_RGBA_H
