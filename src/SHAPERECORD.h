#ifndef LIBSWF_SHAPERECORD_H
#define LIBSWF_SHAPERECORD_H


#include "DataStream.h"

class SHAPERECORD {
public:
	virtual void readData(DataStream* ds);

	virtual int changeX(int x);
	virtual int changeY(int y);
};


#endif //LIBSWF_SHAPERECORD_H
