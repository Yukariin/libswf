#include "TagStub.h"

TagStub::TagStub(uint16_t tagId, string tagName) : Tag(tagId, tagName) {
}

void TagStub::readData(DataStream *ds) {
}
