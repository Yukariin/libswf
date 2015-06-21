#include <iostream>
#include <zlib.h>

#include "Swf.h"
#include "EndTag.h"
#include "ShowFrameTag.h"
#include "SetBackgroundColorTag.h"
#include "FileAttributesTag.h"
#include "DefineFontAlignZonesTag.h"
#include "DefineFont3Tag.h"
#include "SymbolClassTag.h"
#include "DoABCDefineTag.h"
#include "DefineSceneAndFrameLabelDataTag.h"
#include "DefineFontNameTag.h"
#include "UnknownTag.h"

Swf::Swf() {
}

Swf::Swf(vector<uint8_t > in) {
	vector<uint8_t> out;
	decompress(in, out);

	DataStream ds(out);
	ds.skipBytes(3);  // skip siganture
	version = ds.readUI8();
	fileLength = ds.readUI32();
	frameSize = RECT(&ds);
	ds.skipBytes(1);  // tmpFirstByetOfFrameRate
	frameRate = ds.readUI8();
	frameCount = ds.readUI16();
	readTagList(&ds);
}

void Swf::decompress(vector<uint8_t> in, vector<uint8_t> &out) {
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

Tag* Swf::readTag(DataStream *ds) {
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

Tag* Swf::resolveTag(TagStub *t) {
	Tag *ret;

	DataStream *tds = t->getDataStream();
	switch (t->getId()) {
		case 0:
			ret = new EndTag(tds);
			break;
		case 1:
			ret = new ShowFrameTag(tds);
			break;
		case 9:
			ret = new SetBackgroundColorTag(tds);
			break;
		case 69:
			ret = new FileAttributesTag(tds);
			break;
		case 73:
			ret = new DefineFontAlignZonesTag(tds);
			break;
		case 75:
			ret = new DefineFont3Tag(tds);
			break;
		case 76:
			ret = new SymbolClassTag(tds);
			break;
		case 82:
			ret = new DoABCDefineTag(tds);
			break;
		case 86:
			ret = new DefineSceneAndFrameLabelDataTag(tds);
			break;
		case 88:
			ret = new DefineFontNameTag(tds);
			break;
		default:
			ret = new UnknownTag(t->getId());
	}
	delete t;

	return ret;
}

void Swf::readTagList(DataStream *ds) {
	vector<Tag*> tagList;
	Tag *t;
	while (ds->available() > 0) {
		t = readTag(ds);
		if (t == NULL)
			break;
		cout << t->getName() << endl;
		tagList.insert(tagList.end(), t);
	};
}
