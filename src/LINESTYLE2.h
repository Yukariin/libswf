#ifndef LIBSWF_LINESTYLE2_H
#define LIBSWF_LINESTYLE2_H


#include "LINESTYLE.h"
#include "FILLSTYLE.h"

class LINESTYLE2 : public LINESTYLE {
public:
	unsigned startCapStyle;
	unsigned joinStyle;
	enum joinStyles {
		ROUND_JOIN = 0,
		BEVEL_JOIN = 1,
		MITER_JOIN = 2
	};
	bool hasFillFlag;
	bool noHScaleFlag;
	bool noVScaleFlag;
	bool pixelHintingFlag;
	unsigned reserved;
	bool noClose;
	unsigned endCapStyle;
	enum endCapStyles {
		ROUND_CAP = 0,
		NO_CAP = 1,
		SQUARE_CAP = 2
	};
	uint16_t miterLimitFactor;
	FILLSTYLE fillType;

	LINESTYLE2();
	LINESTYLE2(DataStream* ds, int shapeNum);

	void readData(DataStream* ds, int shapeNum);
};


#endif //LIBSWF_LINESTYLE2_H
