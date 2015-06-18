#ifndef LIBSWF_FILLSTYLEARRAY_H
#define LIBSWF_FILLSTYLEARRAY_H


#include <vector>

#include "FILLSTYLE.h"

class FILLSTYLEARRAY {
public:
	std::vector<FILLSTYLE> fillStyles;

	FILLSTYLEARRAY();
	FILLSTYLEARRAY(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_FILLSTYLEARRAY_H
