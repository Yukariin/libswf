#ifndef LIBSWF_FILLSTYLE_H
#define LIBSWF_FILLSTYLE_H


#include <stdint.h>

#include "RGB.h"
#include "MATRIX.h"

class FILLSTYLE {
public:
	uint8_t fillStyleType;
	enum fillStyleTypes {
		SOLID = 0x0,
		LINEAR_GRADIENT = 0x10,
		RADIAL_GRADIENT = 0x12,
		FOCAL_RADIAL_GRADIENT = 0x13,
		REPEATING_BITMAP = 0x40,
		CLIPPED_BITMAP = 0x41,
		NON_SMOOTHED_REPEATING_BITMAP = 0x42,
		NON_SMOOTHED_CLIPPED_BITMAP = 0x43
	};
	bool inShape3;
	RGB color;
	MATRIX gradientMatrix;
	int gradient;
	int bitmapId;
	MATRIX bitmapMatrix;

	FILLSTYLE();
	FILLSTYLE(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_FILLSTYLE_H
