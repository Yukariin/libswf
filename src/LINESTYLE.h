#ifndef LIBSWF_LINESTYLE_H
#define LIBSWF_LINESTYLE_H


#include <stdint.h>

#include "RGB.h"

class LINESTYLE {
public:
	uint16_t width;
	RGB color;

	LINESTYLE();
	LINESTYLE(DataStream* ds, int shapeNum);

	virtual void readData(DataStream* ds, int shapeNum);
};


#endif //LIBSWF_LINESTYLE_H
