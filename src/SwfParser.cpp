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
#include "UnknownTag.h"
#include "SymbolClassTag.h"


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
	uint16_t tagId = tagIdAndLength >> 6;

	uint32_t tagLength = (uint32_t) tagIdAndLength & 0x3F;
	if (tagLength == 0x3F) {
		tagLength = ds->readUI32();
	}
	if (tagLength > ds->available())
		tagLength = (uint32_t) ds->available();

	uint8_t *tagData = ds->readBytes(tagLength);
	DataStream *tagDataStream = new DataStream(tagData, tagLength);
	delete [] tagData;

	TagStub *ret = new TagStub(tagId, "UnresolvedTag", tagDataStream);


	return resolveTag(ret);
}

Tag* SwfParser::resolveTag(TagStub *t) {
	Tag *ret;
	switch (t->getId()) {
		case 0:
			ret = new EndTag(t->getDataStream());
			break;
		case 1:
			ret = new ShowFrameTag(t->getDataStream());
			break;
		case 9:
			ret = new SetBackgroundColorTag(t->getDataStream());
			break;
		case 69:
			ret = new FileAttributesTag(t->getDataStream());
			break;
		case 75:
			ret = new DefineFont3Tag(t->getDataStream());
			break;
		case 76:
			ret = new SymbolClassTag(t->getDataStream());
			break;
		case 82:
			ret = new DoABCDefineTag(t->getDataStream());
			break;
		case 86:
			ret = new DefineSceneAndFrameLabelDataTag(t->getDataStream());
			break;
		case 88:
			ret = new DefineFontNameTag(t->getDataStream());
			break;
		default:
			ret = new UnknownTag(t->getId());
	}
	delete t;

	return ret;
}

void SwfParser::readTagList() {
	vector<Tag*> tagList;
	Tag *t;
	while (ds->available() > 0) {
		t = readTag();
		if (t == NULL)
			break;
		cout << t->getName() << endl;
		tagList.insert(tagList.end(), t);
	};
}

