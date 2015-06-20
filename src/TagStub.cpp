#include "TagStub.h"

TagStub::TagStub(uint16_t tagId, string tagName, DataStream *tagDataStream) : Tag(tagId, tagName) {
	this->tagDataStream = tagDataStream;
}

TagStub::~TagStub() {
	delete tagDataStream;
}

void TagStub::readData(DataStream *ds) {
}

