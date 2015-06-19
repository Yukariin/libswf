#ifndef LIBSWF_DEFINEFONTNAMETAG_H
#define LIBSWF_DEFINEFONTNAMETAG_H


#include "Tag.h"

class DefineFontNameTag : public Tag {
public:
	uint16_t id = 88;

	uint16_t fontId;
	string fontName;
	string fontCopyright;

	DefineFontNameTag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_DEFINEFONTNAMETAG_H
