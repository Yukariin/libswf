#include "UnknownTag.h"

UnknownTag::UnknownTag(uint16_t tagId) : Tag(tagId, "Unknown") {
}

void UnknownTag::readData(DataStream *ds) {
}

string UnknownTag::getName() {
	return Tag::getName() + " (ID=" + to_string(id) + ")";
}
