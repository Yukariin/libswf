#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <zlib.h>
#include <assert.h>

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
#include "DefineFontAlignZonesTag.h"


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
		assert(inputFile);
		inputFile.unsetf(ios::skipws);

		istream_iterator<uint8_t> b(inputFile), e;
		const vector<uint8_t> data(b, e);

		readFromRawData(data);
	}
}

void SwfParser::readFromRawData(vector<uint8_t> data) {
	if (data.size() < 8) {
		return;
	}

	vector<uint8_t> decompressed;
	decompress(data, decompressed);
	ds = new DataStream(decompressed);
	swf->compression = ds->readCompression();
	swf->version = ds->readUI8();
	swf->fileLength = ds->readUI32();
	swf->frameSize = RECT(ds);
	ds->skipBytes(1);  // Skip first byte of frameRate because this looks like big-endian instead little
	swf->frameRate = ds->readUI8();
	swf->frameCount = ds->readUI16();
	readTagList();
}

void SwfParser::readFromRawData(uint8_t *data, size_t dataLength)
{
	if (dataLength < 8) {
		return;
	}

	readFromRawData(vector<uint8_t>(data, data + dataLength));
}

void SwfParser::decompress(vector<uint8_t> in, vector<uint8_t> &out) {
	vector<uint8_t> header(8);
	if(in.size() < 8)
		return;

	// Get uncompressed header part from input
	header = vector<uint8_t>(in.begin(), in.begin() + 8);

	// And read it
	DataStream ds(header);
	string signature = ds.readString(3);
	uint8_t version = ds.readUI8();
	uint32_t fileSize = ds.readUI32();

	// Copy header to output
	out.insert(out.end(), header.begin(), header.end());

	switch (header[0]) {
		case 'C': { // CWS, CFX
			// Get compressed body part from input
			vector<uint8_t> compressedData = vector<uint8_t>(in.begin() + 8, in.end());

			// Create temporary vector for decompression results
			unsigned long uncompressedDataSize = (fileSize - 8);
			vector<uint8_t> uncompressedData(uncompressedDataSize);

			// Decompress!
			int err = uncompress(uncompressedData.data(), &uncompressedDataSize, compressedData.data(), compressedData.size());
			if (err != Z_OK) {
				cerr << err << endl;
				exit(1);
			}

			// Copy decompressed data to output
			out.insert(out.end(), uncompressedData.begin(), uncompressedData.end());

			break;
		}
		default:  // FWS, GFX
			// Copy data to output
			out.insert(out.end(), in.begin() + 8, in.end());
			break;
	}
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

	DataStream *tagDataStream = new DataStream(ds->readBytes(tagLength));
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
		case 73:
			ret = new DefineFontAlignZonesTag(t->getDataStream());
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
