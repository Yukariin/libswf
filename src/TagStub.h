#ifndef LIBSWF_TAGSTUB_H
#define LIBSWF_TAGSTUB_H


#include "Tag.h"

class TagStub : public Tag {
public:
	TagStub(uint16_t tagId, string tagName, DataStream* tagDataStream);
	~TagStub();

	void readData(DataStream* ds);

	DataStream* getDataStream();

private:
	DataStream *tagDataStream;
};


#endif //LIBSWF_TAGSTUB_H
