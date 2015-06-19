#ifndef LIBSWF_STYLECHANGERECORD_H
#define LIBSWF_STYLECHANGERECORD_H


#include "SHAPERECORD.h"
#include "FILLSTYLEARRAY.h"
#include "LINESTYLEARRAY.h"

class StyleChangeRecord : public SHAPERECORD {
public:
	static const bool typeFlag = false;
	bool stateNewStyles;
	bool stateLineStyle;
	bool stateFillStyle1;
	bool stateFillStyle0;
	bool stateMoveTo;
	int moveBits;
	int moveDeltaX;
	int moveDeltaY;
	int fillStyle0;
	int fillStyle1;
	int lineStyle;
	FILLSTYLEARRAY fillStyles;
	LINESTYLEARRAY lineStyles;
	int numFillBits;
	int numLineBits;

	StyleChangeRecord(DataStream* ds, int fillBits, int lineBits, int shapeNum);

	void readData(DataStream* ds, int fillBits, int lineBits, int shapeNum);
	int changeX(int x);
	int changeY(int y);
};


#endif //LIBSWF_STYLECHANGERECORD_H
