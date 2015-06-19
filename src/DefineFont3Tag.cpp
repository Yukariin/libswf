#include <iostream>
#include "DefineFont3Tag.h"

DefineFont3Tag::DefineFont3Tag(DataStream *ds) {
	readData(ds);
}

void DefineFont3Tag::readData(DataStream *ds) {
	fontId = ds->readUI16();
	fontFlagsHasLayout = ds->readUB(1) == 1;
	fontFlagsShiftJIS = ds->readUB(1) == 1;
	fontFlagsSmallText = ds->readUB(1) == 1;
	fontFlagsANSI = ds->readUB(1) == 1;
	fontFlagsWideOffsets = ds->readUB(1) == 1;
	fontFlagsWideCodes = ds->readUB(1) == 1;
	fontFlagsItalic = ds->readUB(1) == 1;
	fontFlagsBold = ds->readUB(1) == 1;
	languageCode = ds->readLANGCODE();
	uint8_t fontNameLen = ds->readUI8();
	fontName = ds->readString(fontNameLen);

	uint16_t numGlyphs = ds->readUI16();
	uint32_t offsetTable [numGlyphs];
	long index = ds->getIndex();
	for (int i = 0; i < numGlyphs; i++) {
		if (fontFlagsWideOffsets)
			offsetTable[i] = ds->readUI32();
		else
			offsetTable[i] = ds->readUI16();
	}

	uint32_t codeTableOffset;
	if (numGlyphs > 0) {
		if (fontFlagsWideOffsets)
			codeTableOffset = ds->readUI32(); //codeTableOffset
		else
			codeTableOffset = ds->readUI16(); //codeTableOffset
	}

	for (int i = 0; i < numGlyphs; i++) {
		ds->seek(index + offsetTable[i]);
		glyphShapeTable.push_back(ds->readSHAPE(1));
	}

	for (int i = 0; i < numGlyphs; i++) {
		if (fontFlagsWideCodes)
			codeTable.push_back(ds->readUI16());
		else
			codeTable.push_back(ds->readUI8());
	}

	if (fontFlagsHasLayout) {
		fontAscent = ds->readUI16();
		fontDescent = ds->readUI16();
		fontLeading = ds->readSI16();

		for (int i = 0; i < numGlyphs; i++) {
			fontAdvanceTable.push_back(ds->readSI16());
		}
		for (int i = 0; i < numGlyphs; i++) {
			fontBoundsTable.push_back(RECT(ds));
		}
		uint16_t kerningCount = ds->readUI16();
		for (int i = 0; i < kerningCount; i++) {
			//fontKerningTable.push_back();
		}
	}
}
