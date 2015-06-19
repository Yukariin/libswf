#ifndef LIBSWF_LINESTYLEARRAY_H
#define LIBSWF_LINESTYLEARRAY_H


#include <vector>

#include "DataStream.h"
#include "LINESTYLE.h"

class LINESTYLEARRAY {
public:
	std::vector<LINESTYLE> lineStyles;

	LINESTYLEARRAY();
	LINESTYLEARRAY(DataStream* ds, int shapeNum);

	void readData(DataStream* ds, int shapeNum);
};


#endif //LIBSWF_LINESTYLEARRAY_H
