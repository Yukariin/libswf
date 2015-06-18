#ifndef LIBSWF_GRADRECORD_H
#define LIBSWF_GRADRECORD_H


#include "DataStream.h"
#include "RGB.h"

class GRADRECORD {
public:
	int ratio;
	bool inShape3;
	RGB color;

	GRADRECORD();
	GRADRECORD(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_GRADRECORD_H
