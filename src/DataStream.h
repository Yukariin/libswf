#ifndef LIBSWF_DATASTREAM_H
#define LIBSWF_DATASTREAM_H


#include <stdint.h>
#include <string>
#include <glob.h>

#include "LANGCODE.h"
#include "SwfCompression.h"
#include "SHAPE.h"
#include "SHAPERECORD.h"

using namespace std;

class DataStream {
public:
	DataStream(DataStream* ds);
	DataStream(uint8_t* data, size_t dataLength);
	~DataStream();

	// Read base types
	uint8_t readUI8();
	uint16_t readUI16();
	uint32_t readUI32();
	uint64_t readUI64();
	int8_t readSI8();
	int16_t readSI16();
	int32_t readSI32();
	int64_t readSI64();
	uint64_t readUB(unsigned nBits);
	int64_t readSB(unsigned nBits);
	uint32_t readEncodedU32();
	string readString();
    string readString(long len);

	LANGCODE readLANGCODE();
	SwfCompression readCompression();
	SHAPE readSHAPE();
	SHAPERECORD* readSHAPERECORD(int fillBits, int lineBits);
	vector<SHAPERECORD*> readSHAPERECORDS(int fillBits, int lineBits);

	// Base read methods
	uint8_t* readBytes(long len);
	void alignByte();
	long available();
	uint8_t read();
	int readNoBitReset();
	void skipBytes(long count);
	long getIndex();
	void seek(long index);

private:
	uint8_t *data;
	size_t dataLength;
	long index = 0;
	int bitIndex = 0;
	int tempByte = 0;
};


#endif //LIBSWF_DATASTREAM_H
