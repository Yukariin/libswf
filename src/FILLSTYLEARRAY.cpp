#include "FILLSTYLEARRAY.h"

FILLSTYLEARRAY::FILLSTYLEARRAY() {
}


FILLSTYLEARRAY::FILLSTYLEARRAY(DataStream *ds, int shapeNum) {
	readData(ds, shapeNum);
}

void FILLSTYLEARRAY::readData(DataStream *ds, int shapeNum) {
	uint16_t fillStyleCount = ds->readUI8();
	if (((shapeNum == 2) || (shapeNum == 3) || (shapeNum == 4/*?*/)) && (fillStyleCount == 0xFF)) {
		fillStyleCount = ds->readUI16();
	}

	for (int i = 0; i < fillStyleCount; i++) {
		fillStyles.push_back(FILLSTYLE(ds, shapeNum));
	}
}
