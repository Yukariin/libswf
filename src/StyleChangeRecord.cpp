#include "StyleChangeRecord.h"

int StyleChangeRecord::changeX(int x) {
	if (stateMoveTo) {
		return moveDeltaX;
	}
	return x;
}

int StyleChangeRecord::changeY(int y) {
	if (stateMoveTo) {
		return moveDeltaY;
	}
	return y;
}

StyleChangeRecord::StyleChangeRecord(DataStream *ds, int fillBits, int lineBits, int shapeNum) {
	readData(ds, fillBits, lineBits, shapeNum);
}

void StyleChangeRecord::readData(DataStream *ds, int fillBits, int lineBits, int shapeNum) {
	stateNewStyles = ds->readUB(1) == 1;
	stateLineStyle = ds->readUB(1) == 1;
	stateFillStyle1 = ds->readUB(1) == 1;
	stateFillStyle0 = ds->readUB(1) == 1;
	stateMoveTo = ds->readUB(1) == 1;
	if ((!stateNewStyles) && (!stateLineStyle) && (!stateFillStyle1) && (!stateFillStyle0) && (!stateMoveTo))
		return;
	if (stateMoveTo) {
		moveBits = (int) ds->readUB(5);
		moveDeltaX = (int) ds->readSB(moveBits);
		moveDeltaY = (int) ds->readSB(moveBits);
	}
	if (stateFillStyle0) {
		fillStyle0 = (int) ds->readUB(fillBits);
	}
	if (stateFillStyle1) {
		fillStyle1 = (int) ds->readUB(fillBits);
	}
	if (stateLineStyle) {
		lineStyle = (int) ds->readUB(lineBits);
	}
	if (stateNewStyles) {
		fillStyles = FILLSTYLEARRAY(ds, shapeNum);
		lineStyles = LINESTYLEARRAY(ds, shapeNum);

		numFillBits = (int) ds->readUB(4);
		numLineBits = (int) ds->readUB(4);
	}
}
