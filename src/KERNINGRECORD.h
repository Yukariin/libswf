#ifndef LIBSWF_KERNINGRECORD_H
#define LIBSWF_KERNINGRECORD_H


#include <stdint.h>

#include "SwfBaseTypes.h"
#include "DataStream.h"

class KERNINGRECORD {
public:
	uint16_t fontKerningCode1;
	uint16_t fontKerningCode2;
	int16_t fontKerningAdjustment;

	KERNINGRECORD(DataStream* ds, bool fontFlagsWideCodes);

	void readData(DataStream* ds, bool fontFlagsWideCodes);
};


#endif //LIBSWF_KERNINGRECORD_H
