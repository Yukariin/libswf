#ifndef LIBSWF_FOCALGRADIENT_H
#define LIBSWF_FOCALGRADIENT_H


#include "GRADIENT.h"

class FOCALGRADIENT : public GRADIENT {
public:
	float focalPoint;

	FOCALGRADIENT(DataStream* ds, int shapeNum);

	void readData(DataStream* ds, int shapeNum);
};


#endif //LIBSWF_FOCALGRADIENT_H
