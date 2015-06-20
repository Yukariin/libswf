#include "ShowFrameTag.h"

ShowFrameTag::ShowFrameTag(DataStream *ds) : Tag(ID, "ShowFrame") {
	readData(ds);
}

void ShowFrameTag::readData(DataStream *ds) {
}
