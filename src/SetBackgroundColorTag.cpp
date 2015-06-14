//
// Created by yukarin on 6/5/15.
//

#include "SetBackgroundColorTag.h"

SetBackgroundColorTag::SetBackgroundColorTag(DataStream *ds) {
	readData(ds);
}

void SetBackgroundColorTag::readData(DataStream *ds) {
    backgroundColor = ds->readRGB();
}
