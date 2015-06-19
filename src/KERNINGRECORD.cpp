#include "KERNINGRECORD.h"

KERNINGRECORD::KERNINGRECORD(DataStream *ds, bool fontFlagsWideCodes) {
	readData(ds, fontFlagsWideCodes);
}

void KERNINGRECORD::readData(DataStream *ds, bool fontFlagsWideCodes) {
	if (fontFlagsWideCodes) {
		fontKerningCode1 = ds->readUI16();
		fontKerningCode2 = ds->readUI16();
	} else {
		fontKerningCode1 = ds->readUI8();
		fontKerningCode2 = ds->readUI8();
	}
	fontKerningAdjustment = ds->readSI16();
}
