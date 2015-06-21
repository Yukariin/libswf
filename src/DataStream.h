#ifndef LIBSWF_DATASTREAM_H
#define LIBSWF_DATASTREAM_H


#include <stdint.h>
#include <string>
#include <glob.h>
#include <vector>

#include "LANGCODE.h"
#include "SwfCompression.h"
#include "SHAPERECORD.h"

using namespace std;

class DataStream {
public:
	DataStream();
	DataStream(DataStream* ds);
	DataStream(vector<uint8_t> data);
	DataStream(uint8_t* data, size_t dataLength);

	// Read base types
	uint8_t readUI8();
	uint16_t readUI16();
	uint32_t readUI32();
	uint64_t readUI64();
	int8_t readSI8();
	int16_t readSI16();
	int32_t readSI32();
	float readFIXED();
	float readFIXED8();
	float readFLOAT16();
	float readFLOAT();
	double readDOUBLE();
	uint32_t readEncodedU32();
	uint64_t readUB(unsigned nBits);
	int64_t readSB(unsigned nBits);
	string readString();
	string readString(long len);

	LANGCODE readLANGCODE();
	SwfCompression readCompression();
	SHAPERECORD* readSHAPERECORD(int fillBits, int lineBits, int shapeNum);
	vector<SHAPERECORD*> readSHAPERECORDS(int fillBits, int lineBits, int shapeNum);

	// Base read methods
	uint8_t read();
	int readNoBitReset();
	vector<uint8_t> readBytes(long len);

	//Base write methods
	//void write(uint8_t);

	// Base data stream methods
	void alignByte();
	long available();
	void skipBytes(long count);
	long getIndex();
	void seek(long index);

private:
	vector<uint8_t> data;
	// uint8_t *data;
	//size_t dataLength;
	long index = 0;
	int bitIndex = 0;
	int tempByte = 0;
};


#endif //LIBSWF_DATASTREAM_H
