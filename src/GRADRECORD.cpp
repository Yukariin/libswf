#include "GRADRECORD.h"
#include "RGBA.h"

GRADRECORD::GRADRECORD() {

}

GRADRECORD::GRADRECORD(DataStream *ds, int shapeNum) {
	readData(ds, shapeNum);
}

void GRADRECORD::readData(DataStream *ds, int shapeNum) {
	ratio = ds->readUI8();
	if (shapeNum >= 3) {
		color = RGBA(ds);
	} else {
		color = RGB(ds);
	}
}
