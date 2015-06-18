#include "StraightEdgeRecord.h"

StraightEdgeRecord::StraightEdgeRecord(DataStream *ds) {
	readData(ds);
}

void StraightEdgeRecord::readData(DataStream *ds) {
	numBits = (int) ds->readUB(4);
	generalLineFlag = ds->readUB(1) == 1;
	if (!generalLineFlag) {
		vertLineFlag = ds->readUB(1) == 1;
	}
	if (generalLineFlag || (!vertLineFlag)) {
		deltaX = (int) ds->readSB(numBits + 2);
	}
	if (generalLineFlag || (vertLineFlag)) {
		deltaY = (int) ds->readSB(numBits + 2);
	}
}

int StraightEdgeRecord::changeX(int x) {
	if (generalLineFlag) {
		return x + deltaX;
	} else if (vertLineFlag) {
		return x;
	} else {
		return x + deltaX;
	}
}

int StraightEdgeRecord::changeY(int y) {
	if (generalLineFlag) {
		return y + deltaY;
	} else if (vertLineFlag) {
		return y + deltaY;
	} else {
		return y;
	}
}
