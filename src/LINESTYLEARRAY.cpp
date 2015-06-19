#include "LINESTYLEARRAY.h"
#include "LINESTYLE2.h"

LINESTYLEARRAY::LINESTYLEARRAY() {

}

LINESTYLEARRAY::LINESTYLEARRAY(DataStream *ds, int shapeNum) {
	readData(ds, shapeNum);
}

void LINESTYLEARRAY::readData(DataStream *ds, int shapeNum) {
	uint16_t lineStyleCount = ds->readUI8();
	if (lineStyleCount == 0xFF) {
		lineStyleCount = ds->readUI16();
	}
	if ((shapeNum == 1 || shapeNum == 2 || shapeNum == 3)) {
		for (int i = 0; i < lineStyleCount; i++) {
			lineStyles.push_back(LINESTYLE(ds, shapeNum));
		}
	} else if (shapeNum == 4) {
		for (int i = 0; i < lineStyleCount; i++) {
			lineStyles.push_back(LINESTYLE2(ds, shapeNum));
		}
	}
}
