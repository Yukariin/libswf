#include "FILLSTYLEARRAY.h"

FILLSTYLEARRAY::FILLSTYLEARRAY() {
}


FILLSTYLEARRAY::FILLSTYLEARRAY(DataStream *ds) {
	readData(ds);
}

void FILLSTYLEARRAY::readData(DataStream *ds) {
	uint16_t fillStyleCount = ds->readUI8();
	if (fillStyleCount == 0xFF) {
		fillStyleCount = ds->readUI16();
	}

	for (int i = 0; i < fillStyleCount; i++) {
		fillStyles.push_back(FILLSTYLE(ds));
	}
}
