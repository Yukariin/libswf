#include <assert.h>
#include <iostream>
#include <sstream>

#include "DataStream.h"

DataStream::DataStream(DataStream *ds) {
	DataStream(ds->data, ds->dataLength);
}

DataStream::DataStream(uint8_t *data, size_t dataLength) {
	this->data = new uint8_t [dataLength];
	this->dataLength = dataLength;
	index = 0;
	bitIndex = 0;
	tempByte = 0;
	copy(data, data + dataLength, this->data);
}

DataStream::~DataStream()
{
	delete data;
}

uint8_t DataStream::readUI8() {
	return read();
}

uint16_t DataStream::readUI16() {
	return ((uint16_t)read() + ((uint16_t)read() << 8));
}

uint32_t DataStream::readUI32() {
	return ((uint32_t)read() + ((uint32_t)read() << 8) + ((uint32_t)read() << 16) + ((uint32_t)read() << 24));
}

uint64_t DataStream::readUI64() {
	return ((uint64_t)read() + ((uint64_t)read() << 8) + ((uint64_t)read() << 16) + ((uint64_t)read() << 24)
			+ ((uint64_t)read() << 32)+ ((uint64_t)read() << 40) + ((uint64_t)read() << 48) + ((uint64_t)read() << 56));
}

int8_t DataStream::readSI8() {
	int ret = read();
	if (ret >= 0x80) {
		ret = -(((~ret) & 0xFF) + 1);
	}

	return (int8_t)ret;
}

int16_t DataStream::readSI16() {
	int ret = readUI16();
	if (ret >= 0x8000) {
		ret = -(((~ret) & 0xFFFF) + 1);
	}

	return (int16_t)ret;
}

int32_t DataStream::readSI32() {
	int ret = readUI32();
	if (ret >= 0x80000000) {
		ret = -(((~ret) & 0xFFFFFFFF) + 1);
	}

	return (int32_t)ret;
}

int64_t DataStream::readSI64() {
	int64_t ret = readUI64();
	if (ret >= 0x8000000000000000) {
		ret = -(((~ret) & 0xFFFFFFFFFFFFFFFF) + 1);
	}

	return (int64_t)ret;
}

uint64_t DataStream::readUB(unsigned nBits) {
	assert(nBits <= 56);
	if (nBits == 0)
		return 0;

	uint64_t ret = 0;
	if (bitIndex == 0) {
		tempByte = readNoBitReset();
	}
	for (unsigned bit = 0; bit < nBits; bit++) {
		int nb = (tempByte >> (7 - bitIndex)) & 1;
		ret += (nb << (nBits - 1 - bit));
		bitIndex++;
		if (bitIndex == 8) {
			bitIndex = 0;
			if (bit != nBits - 1) {
				tempByte = readNoBitReset();
			}
		}
	}

	return ret;
}

int64_t DataStream::readSB(unsigned nBits) {
	uint64_t ret = readUB(nBits);
	if (ret >> (nBits - 1)) {
		ret |= (0xFFFFFFFFFFFFFFFF >> nBits) << nBits;
	}

	return (int64_t)ret;
}

uint32_t DataStream::readEncodedU32() {
	uint32_t ret = read();
	if (!(ret & 0x00000080))
		return ret;
	ret = (ret & 0x0000007F) | (read()) << 7;
	if(!(ret & 0x00004000))
		return ret;
	ret = (ret & 0x00003FFF) | (read()) << 14;
	if (!(ret & 0x00200000))
		return ret;
	ret = (ret & 0x001FFFFF) | (read()) << 21;
	if (!(ret & 0x10000000))
		return ret;
	ret = (ret & 0xFFFFFFFF) | (read()) << 28;

	return ret;
}

string DataStream::readString() {
	ostringstream ret;
	uint8_t r;
	while (true) {
		r = read();
		if (r == 0) {
			return ret.str();
		}
		ret << r;
	}
}

string DataStream::readString(long len) {
	ostringstream ret;
	for (int i = 0; i < len; i++) {
		ret << read();
	}

	return ret.str();
}

RGB DataStream::readRGB() {
	RGB r;
	r.red = readUI8();
	r.green = readUI8();
	r.blue = readUI8();

	return r;
}

RECT DataStream::readRect() {
	RECT ret;
	uint64_t nBits = readUB(5);
	ret.nBits = nBits;
	ret.Xmin = readSB(nBits);
	ret.Xmax = readSB(nBits);
	ret.Ymin = readSB(nBits);
	ret.Ymax = readSB(nBits);
	alignByte();

	return ret;
}

LANGCODE DataStream::readLANGCODE() {
	LANGCODE ret;
	ret =  LANGCODE(readUI8());
	return ret;
}

SwfCompression DataStream::readCompression() {
	SwfCompression ret;
	ret = SwfCompression(readUI8());
	skipBytes(2);

	return ret;
}

SHAPE DataStream::readSHAPE()
{
	SHAPE ret;
	ret.numFillBits = (int) readUB(4);
	ret.numLineBits = (int) readUB(4);
	//ret.shapeRecords = ;

	return ret;
}

SHAPERECORD DataStream::readSHAPERECORD()
{
	SHAPERECORD ret;
	int typeFlag = (int) readUB(1);
	if(typeFlag == 0) {
		bool stateNewStyles = readUB(1) == 1;
		bool stateLineStyle = readUB(1) == 1;
		bool stateFillStyle1 = readUB(1) == 1;
		bool stateFillStyle0 = readUB(1) == 1;
		bool stateMoveTo = readUB(1) == 1;
	} else {

	}

	return ret;
}


int DataStream::readBytes(uint8_t *bytes, long len) {
	if (len <= 0)
		return 0;

	bitIndex = 0;
	copy(data + index, data + index + len, bytes);
	index += len;

	return (int)len;
}

uint8_t DataStream::read() {
	bitIndex = 0;
	uint8_t ret = data[index++];

	return ret;
}

void DataStream::alignByte() {
	bitIndex = 0;
}

int DataStream::readNoBitReset() {
	int ret = data[index++];

	return ret;
}

long DataStream::available() {
	return (dataLength - index);
}

void DataStream::skipBytes(long count) {
	if (count <= 0) {
		return;
	}

	bitIndex = 0;
	index += count;
	if (available() < 0)
		return;
}

long DataStream::getIndex() {
	return index;
}

void DataStream::seek(long index) {
	this->index = index;
}
