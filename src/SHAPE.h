#ifndef LIBSWF_SHAPE_H
#define LIBSWF_SHAPE_H


#include <vector>
#include "SHAPERECORD.h"
#include "DataStream.h"

using namespace std;

class SHAPE {
public:
	int numFillBits;
	int numLineBits;
	vector<SHAPERECORD*> shapeRecords;

	SHAPE(DataStream* ds, int shapeNum);

	void readData(DataStream* ds, int shapeNum);
};


#endif //LIBSWF_SHAPE_H
