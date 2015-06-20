#ifndef LIBSWF_DEFINEFONT3TAG_H
#define LIBSWF_DEFINEFONT3TAG_H


#include <vector>

#include "Tag.h"
#include "LANGCODE.h"
#include "SHAPE.h"
#include "RECT.h"
#include "KERNINGRECORD.h"

class DefineFont3Tag : public Tag {
public:
	static const uint16_t ID = 75;

	uint16_t fontId;
	bool fontFlagsHasLayout;
	bool fontFlagsShiftJIS;
	bool fontFlagsSmallText;
	bool fontFlagsANSI;
	bool fontFlagsWideOffsets;
	bool fontFlagsWideCodes;
	bool fontFlagsItalic;
	bool fontFlagsBold;
	LANGCODE languageCode;
	string fontName;
	vector<SHAPE> glyphShapeTable;
	vector<uint16_t> codeTable;
	uint16_t fontAscent;
	uint16_t fontDescent;
	int16_t fontLeading;
	vector<int16_t> fontAdvanceTable;
	vector<RECT> fontBoundsTable;
	vector<KERNINGRECORD> fontKerningTable;

	DefineFont3Tag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_DEFINEFONT3TAG_H
