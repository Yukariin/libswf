#ifndef LIBSWF_TAGSTUB_H
#define LIBSWF_TAGSTUB_H


#include "Tag.h"

class TagStub : public Tag {
public:
	DataStream *tagDataStream;

	TagStub(uint16_t tagId, string tagName, DataStream* tagDataStream);
	~TagStub();

	void readData(DataStream* ds);
};


#endif //LIBSWF_TAGSTUB_H
