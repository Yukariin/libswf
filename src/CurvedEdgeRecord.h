#ifndef LIBSWF_CURVEDEDGERECORD_H
#define LIBSWF_CURVEDEDGERECORD_H


#include "DataStream.h"

class CurvedEdgeRecord : public SHAPERECORD {
public:
	static const bool typeFlag = true;
	static const bool straightFlag = false;
	unsigned numBits;
	int controlDeltaX;
	int controlDeltaY;
	int anchorDeltaX;
	int anchorDeltaY;

	CurvedEdgeRecord(DataStream* ds);

	void readData(DataStream* ds);
	int changeX(int x);
	int changeY(int y);
};


#endif //LIBSWF_CURVEDEDGERECORD_H
