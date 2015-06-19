#include "LINESTYLE2.h"
#include "RGBA.h"

LINESTYLE2::LINESTYLE2() {

}

LINESTYLE2::LINESTYLE2(DataStream *ds, int shapeNum) {
	readData(ds, shapeNum);
}

void LINESTYLE2::readData(DataStream *ds, int shapeNum) {
	width = ds->readUI16();
	startCapStyle = (unsigned) ds->readUB(2);
	joinStyle = (unsigned) ds->readUB(2);
	hasFillFlag = ds->readUB(1) == 1;
	noHScaleFlag = ds->readUB(1) == 1;
	noVScaleFlag = ds->readUB(1) == 1;
	pixelHintingFlag = ds->readUB(1) == 1;
	reserved = (unsigned) ds->readUB(5);
	noClose = ds->readUB(1) == 1;
	endCapStyle = (unsigned) ds->readUB(2);
	if (joinStyle == joinStyles::MITER_JOIN) {
		miterLimitFactor = ds->readUI16();
	}
	if (!hasFillFlag) {
		color = RGBA(ds);
	} else {
		fillType = FILLSTYLE(ds, shapeNum);
	}
}
