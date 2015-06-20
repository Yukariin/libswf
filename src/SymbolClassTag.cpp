#include "SymbolClassTag.h"

SymbolClassTag::SymbolClassTag(DataStream *ds) : Tag(ID, "SymbolClass") {
	readData(ds);
}

void SymbolClassTag::readData(DataStream *ds) {
	uint16_t numSymbols = ds->readUI16();
	for (int i = 0; i < numSymbols; i++) {
		tags.push_back(ds->readUI16());
		names.push_back(ds->readString());
	}
}
