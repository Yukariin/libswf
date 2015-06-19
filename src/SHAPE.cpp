#include "SHAPE.h"

SHAPE::SHAPE(DataStream *ds, int shapeNum) {
	readData(ds, shapeNum);
}

void SHAPE::readData(DataStream *ds, int shapeNum) {
	numFillBits = (int) ds->readUB(4);
	numLineBits = (int) ds->readUB(4);
	shapeRecords = ds->readSHAPERECORDS(numFillBits, numLineBits, shapeNum);

}
