#include "GRADRECORD.h"

GRADRECORD::GRADRECORD() {

}

GRADRECORD::GRADRECORD(DataStream *ds) {
	readData(ds);
}

void GRADRECORD::readData(DataStream *ds) {
	ratio = ds->readUI8();
	color = RGB(ds);
}
