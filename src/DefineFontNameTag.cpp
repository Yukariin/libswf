#include <iostream>
#include "DefineFontNameTag.h"

DefineFontNameTag::DefineFontNameTag(DataStream *ds) {
	readData(ds);
}

void DefineFontNameTag::readData(DataStream *ds) {
	fontId = ds->readUI16();
	fontName = ds->readString();
	fontCopyright = ds->readString();
}
