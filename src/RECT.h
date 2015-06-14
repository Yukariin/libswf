//
// Created by yukarin on 5/30/15.
//

#ifndef LIBSWF_RECT_H
#define LIBSWF_RECT_H


#include <stdint.h>
#include "SwfBaseTypes.h"

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
};


#endif //LIBSWF_RECT_H
