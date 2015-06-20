#ifndef LIBSWF_TAGSTUB_H
#define LIBSWF_TAGSTUB_H


#include "Tag.h"

class TagStub : public Tag {
public:
	TagStub(uint16_t tagId, string tagName);

	void readData(DataStream* ds);
};


#endif //LIBSWF_TAGSTUB_H
