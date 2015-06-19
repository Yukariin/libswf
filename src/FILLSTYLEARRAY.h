#ifndef LIBSWF_FILLSTYLEARRAY_H
#define LIBSWF_FILLSTYLEARRAY_H


#include <vector>

#include "FILLSTYLE.h"

class FILLSTYLEARRAY {
public:
	std::vector<FILLSTYLE> fillStyles;

	FILLSTYLEARRAY();
	FILLSTYLEARRAY(DataStream* ds, int shapeNum);

	void readData(DataStream* ds, int shapeNum);
};


#endif //LIBSWF_FILLSTYLEARRAY_H
