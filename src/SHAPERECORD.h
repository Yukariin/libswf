#ifndef LIBSWF_SHAPERECORD_H
#define LIBSWF_SHAPERECORD_H


#include "DataStream.h"

class SHAPERECORD {
public:
	virtual void readData(DataStream* ds) = 0;

	virtual int changeX(int x) = 0;
	virtual int changeY(int y) = 0;
};


#endif //LIBSWF_SHAPERECORD_H
