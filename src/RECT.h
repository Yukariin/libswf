#ifndef LIBSWF_RECT_H
#define LIBSWF_RECT_H


#include <stdint.h>

#include "SwfBaseTypes.h"
#include "DataStream.h"

class RECT {
public:
	uint64_t nBits;
	int64_t Xmin;
	int64_t Xmax;
	int64_t Ymin;
	int64_t Ymax;

	RECT();
	RECT(int64_t Xmin, int64_t Xmax, int64_t Ymin, int64_t Ymax);
	RECT(RECT* r);
	RECT(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_RECT_H
