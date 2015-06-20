#include "SetBackgroundColorTag.h"

SetBackgroundColorTag::SetBackgroundColorTag(DataStream *ds) : Tag(ID, "SetBackgroundColor") {
	readData(ds);
}

void SetBackgroundColorTag::readData(DataStream *ds) {
	backgroundColor = RGB(ds);
}
