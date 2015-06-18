#ifndef LIBSWF_SHAPE_H
#define LIBSWF_SHAPE_H


#include <vector>
#include "SHAPERECORD.h"

using namespace std;

class SHAPE {
public:
	int numFillBits;
	int numLineBits;
	vector<SHAPERECORD*> shapeRecords;
};


#endif //LIBSWF_SHAPE_H
