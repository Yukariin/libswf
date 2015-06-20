#ifndef LIBSWF_SETBACKGROUNDCOLORTAG_H
#define LIBSWF_SETBACKGROUNDCOLORTAG_H


#include "Tag.h"
#include "RGB.h"

class SetBackgroundColorTag : public Tag {
public:
	static const uint16_t ID = 9;

	RGB backgroundColor;

	SetBackgroundColorTag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_SETBACKGROUNDCOLORTAG_H
