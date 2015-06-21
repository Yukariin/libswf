#include "DefineFontAlignZonesTag.h"

DefineFontAlignZonesTag::DefineFontAlignZonesTag(DataStream *ds) : Tag(ID, "DefineFontAlignZones") {
	readData(ds);
}

void DefineFontAlignZonesTag::readData(DataStream *ds) {
	fontId = ds->readUI16();
	CSMTableHint = (uint8_t) ds->readUB(2);
	reserved = (uint8_t) ds->readUB(6) == 1;
	while (ds->available() > 0) {
		zoneTable.push_back(ZONERECORD(ds));
	}
}
