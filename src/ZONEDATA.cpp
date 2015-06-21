#include "ZONEDATA.h"

ZONEDATA::ZONEDATA(DataStream *ds) {
	readData(ds);
}

void ZONEDATA::readData(DataStream *ds) {
	alignmentCoordinate = ds->readFLOAT16();
	range = ds->readFLOAT16();
}

string ZONEDATA::toString() {
	return "[ZONEDATA alignmentCoordinate=" + to_string(alignmentCoordinate) + ", range=" + to_string(range) + "]";
}
