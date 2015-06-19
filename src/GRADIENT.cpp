#include "GRADIENT.h"

GRADIENT::GRADIENT() {

}

GRADIENT::GRADIENT(DataStream *ds, int shapeNum) {
	readData(ds, shapeNum);
}

void GRADIENT::readData(DataStream *ds, int shapeNum) {
	spreadMode = (int) ds->readUB(2);
	interpolationMode = (int) ds->readUB(2);

	int numGradients = (int) ds->readUB(4);
	for (int i = 0; i < numGradients; i++) {
		gradientRecords.push_back(GRADRECORD(ds, shapeNum));
	}
}
