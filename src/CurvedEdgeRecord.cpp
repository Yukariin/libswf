#include "CurvedEdgeRecord.h"

CurvedEdgeRecord::CurvedEdgeRecord(DataStream *ds) {
	readData(ds);
}

void CurvedEdgeRecord::readData(DataStream *ds) {
	numBits = (unsigned) ds->readUB(4);
	controlDeltaX = (int) ds->readSB(numBits + 2);
	controlDeltaY = (int) ds->readSB(numBits + 2);
	anchorDeltaX = (int) ds->readSB(numBits + 2);
	anchorDeltaY = (int) ds->readSB(numBits + 2);
}

int CurvedEdgeRecord::changeX(int x) {
	return x + (controlDeltaX + anchorDeltaX);
}

int CurvedEdgeRecord::changeY(int y) {
	return y + (controlDeltaY + anchorDeltaY);
}
