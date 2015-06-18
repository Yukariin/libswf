#ifndef LIBSWF_STRAIGHTEDGERECORD_H
#define LIBSWF_STRAIGHTEDGERECORD_H


#include "SHAPERECORD.h"
#include "DataStream.h"

class StraightEdgeRecord : public SHAPERECORD {
public:
	static const bool typeFlag = true;
	static const bool straightFlag = true;
	unsigned numBits;
	bool generalLineFlag;
	bool vertLineFlag;
	int deltaX;
	int deltaY;

	StraightEdgeRecord(DataStream* ds);

	void readData(DataStream* ds);
	int changeX(int x);
	int changeY(int y);
};


#endif //LIBSWF_STRAIGHTEDGERECORD_H
