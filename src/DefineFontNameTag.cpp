#include <iostream>
#include "DefineFontNameTag.h"

DefineFontNameTag::DefineFontNameTag(DataStream *ds) : Tag(ID, "DefineFontName") {
	readData(ds);
}

void DefineFontNameTag::readData(DataStream *ds) {
	fontId = ds->readUI16();
	fontName = ds->readString();
	fontCopyright = ds->readString();
}
