#ifndef LIBSWF_MATRIX_H
#define LIBSWF_MATRIX_H


#include "DataStream.h"

class MATRIX {
public:
	bool hasScale;
	int scaleX;
	int scaleY;
	bool hasRotate;
	int rotateSkew0;
	int rotateSkew1;
	int translateX;
	int translateY;
	int nTranslateBits;
	int nRotateBits;
	int nScaleBits;

	MATRIX();
	MATRIX(MATRIX* m);
	MATRIX(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_MATRIX_H
