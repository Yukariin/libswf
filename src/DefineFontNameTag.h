#ifndef LIBSWF_DEFINEFONTNAMETAG_H
#define LIBSWF_DEFINEFONTNAMETAG_H


#include "Tag.h"

class DefineFontNameTag : public Tag {
public:
	static const uint16_t ID = 88;

	uint16_t fontId;
	string fontName;
	string fontCopyright;

	DefineFontNameTag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_DEFINEFONTNAMETAG_H
