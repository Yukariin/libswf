#ifndef LIBSWF_SHOWFRAMETAG_H
#define LIBSWF_SHOWFRAMETAG_H


#include "Tag.h"

class ShowFrameTag : public Tag {
public:
	static const uint16_t ID = 1;

	ShowFrameTag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_SHOWFRAMETAG_H
