#ifndef LIBSWF_DEFINEFONTALIGNZONESTAG_H
#define LIBSWF_DEFINEFONTALIGNZONESTAG_H


#include "Tag.h"
#include "ZONERECORD.h"

class DefineFontAlignZonesTag : public Tag {
public:
	static const uint16_t ID = 73;

	uint16_t fontId;
	uint8_t CSMTableHint;
	bool reserved;
	vector<ZONERECORD> zoneTable;

	DefineFontAlignZonesTag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_DEFINEFONTALIGNZONESTAG_H
