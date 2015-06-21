#ifndef LIBSWF_SWFPARSER_H
#define LIBSWF_SWFPARSER_H


#include <stdint.h>
#include <string>

#include "Swf.h"
#include "SwfCompression.h"
#include "RECT.h"
#include "Tag.h"
#include "RGB.h"
#include "TagStub.h"

using namespace std;

class SwfParser {
public:
	SwfParser();
	SwfParser(Swf* swf);
	~SwfParser();

	void readFromFile(const char* fileName);
	void readFromRawData(vector<uint8_t> data);
	void readFromRawData(uint8_t* data, size_t dataLength);
	static void decompress(vector<uint8_t> in, vector<uint8_t>& out);
	Tag* readTag();
	static Tag* resolveTag(TagStub* t);
	void readTagList();


private:
	Swf *swf;
	DataStream *ds;
};


#endif //LIBSWF_SWFPARSER_H
