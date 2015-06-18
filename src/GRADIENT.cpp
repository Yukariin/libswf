#include "GRADIENT.h"

GRADIENT::GRADIENT() {

}

GRADIENT::GRADIENT(DataStream *ds) {
	readData(ds);
}

void GRADIENT::readData(DataStream *ds) {
	spreadMode = (int) ds->readUB(2);
	interpolationMode = (int) ds->readUB(2);

	int numGradients = (int) ds->readUB(4);
	for (int i = 0; i < numGradients; i++) {
		gradientRecords.push_back(GRADRECORD(ds));
	}
}
