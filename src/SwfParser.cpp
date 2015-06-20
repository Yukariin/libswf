#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>

#include "SwfParser.h"
#include "FileAttributesTag.h"
#include "SetBackgroundColorTag.h"
#include "DefineSceneAndFrameLabelDataTag.h"
#include "DefineFont3Tag.h"
#include "EndTag.h"
#include "DefineFontNameTag.h"
#include "DoABCDefineTag.h"
#include "ShowFrameTag.h"
#include "TagStub.h"


SwfParser::SwfParser() {
	swf = new Swf();
}

SwfParser::SwfParser(Swf *swf) {
	this->swf = swf;
}

SwfParser::~SwfParser() {
	delete swf;
	delete ds;
}

void SwfParser::readFromFile(const char *fileName)
{
	if (fileName) {
		ifstream inputFile (fileName, ios::binary);

		inputFile.seekg (0, inputFile.end);
		size_t length = (size_t) inputFile.tellg();
		inputFile.seekg (0, inputFile.beg);

		cout << length << endl;

		uint8_t data[length];
		inputFile.read((char*)&data, length);

		inputFile.close();

		readFromRawData(data, length);
	}
}

void SwfParser::readFromRawData(uint8_t *data, size_t dataLength)
{
	if (dataLength < 8) {
		return;
	}

	// Create buffer for header and copy header
	uint8_t header [8];
	copy(data, data + 8, header);
	ds = new DataStream(header, sizeof(header));

	swf->compression = ds->readCompression();
	swf->version = ds->readUI8();
	swf->fileLength = ds->readUI32();

	unsigned long bodySize = (swf->fileLength - 8);
	uint8_t body [bodySize];

	if (swf->compression == SwfCompression::NONE) {
		copy(data + 8, data + dataLength, body);
	}
	else if (swf->compression == SwfCompression::ZLIB) {
		unsigned long compressedDataSize = (dataLength - 8);
		uncompress(body, &bodySize, data + 8, compressedDataSize);
	}
	ds = new DataStream(body, sizeof(body));

	swf->frameSize = RECT(ds);
	ds->readUI8();  // Skip first byte of frameRate because this looks like big-endian instead little
	swf->frameRate = ds->readUI8();
	swf->frameCount = ds->readUI16();

	readTagList();
}



Tag* SwfParser::readTag() {
	uint16_t tagIdAndLength = ds->readUI16();
	uint16_t tagId = tagIdAndLength >> 6;  // Upper 10 bits: tag ID

	cout << "Tag ID is: " << (int)tagId << endl;

	uint32_t tagLength = (uint32_t) tagIdAndLength & 0x3F;
	if (tagLength == 0x3F) {
		tagLength = ds->readUI32();
	}
	if (tagLength > ds->available())
		tagLength = (uint32_t) ds->available();

	cout << "Tag length is: " << (int)tagLength << endl;

	Tag *ret = new TagStub(tagId, "UnresolvedTag");

	switch (tagId) {
		case 0:
			ret = new EndTag(ds);
			break;
		case 1:
			ret = new ShowFrameTag(ds);
			break;
		case 9:
			ret = new SetBackgroundColorTag(ds);
			break;
		case 69:
			ret = new FileAttributesTag(ds);
			break;
		case 75:
			ret = new DefineFont3Tag(ds);
			break;
		case 82:
			ds->skipBytes(tagLength); // ret = new DoABCDefineTag(ds);
			break;
		case 86:
			ret = new DefineSceneAndFrameLabelDataTag(ds);
			break;
		case 88:
			ret = new DefineFontNameTag(ds);
			break;
	}

	return ret;
}

void SwfParser::readTagList() {
	vector<Tag*> tagList;
	Tag *t;
	do {
		t = readTag();
		if (t->id)
			tagList.insert(tagList.end(), t);
	} while (!dynamic_cast<EndTag*>(t) && ds->available() > 0);
}
