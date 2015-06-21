#include <iostream>
#include "ZONERECORD.h"

ZONERECORD::ZONERECORD(DataStream *ds) {
	readData(ds);
}

void ZONERECORD::readData(DataStream *ds) {
	uint8_t numZoneData = ds->readUI8();
	for (int i = 0; i < numZoneData; i++) {
		zonedata.push_back(ZONEDATA(ds));
	}
	reserved = ds->readUB(6) == 1;
	zoneMaskY = ds->readUB(1) == 1;
	zoneMaskX = ds->readUB(1) == 1;
}
