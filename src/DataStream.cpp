#include <assert.h>
#include <iostream>
#include <sstream>

#include "DataStream.h"
#include "EndShapeRecord.h"
#include "StyleChangeRecord.h"

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
	ret.shapeRecords = readSHAPERECORDS(ret.numFillBits, ret.numLineBits);

	return ret;
}

SHAPERECORD DataStream::readSHAPERECORD(int fillBits, int lineBits)
{
	SHAPERECORD ret;
	int typeFlag = (int) readUB(1);
	if(typeFlag == 0) {
		bool stateNewStyles = readUB(1) == 1;
		bool stateLineStyle = readUB(1) == 1;
		bool stateFillStyle1 = readUB(1) == 1;
		bool stateFillStyle0 = readUB(1) == 1;
		bool stateMoveTo = readUB(1) == 1;
		if ((!stateNewStyles) && (!stateLineStyle) && (!stateFillStyle1) && (!stateFillStyle0) && (!stateMoveTo))
			ret = EndShapeRecord();
		else {
			StyleChangeRecord scr;
			scr.stateNewStyles = stateNewStyles;
			scr.stateLineStyle = stateLineStyle;
			scr.stateFillStyle1 = stateFillStyle1;
			scr.stateFillStyle0 = stateFillStyle0;
			scr.stateMoveTo = stateMoveTo;
			if (stateMoveTo) {
				scr.moveBits = (int) readUB(5);
				scr.moveDeltaX = (int) readSB(scr.moveBits);
				scr.moveDeltaY = (int) readSB(scr.moveBits);
			}
			if (stateFillStyle0) {
				scr.fillStyle0 = (int) readUB(fillBits);
			}
			if (stateFillStyle1) {
				scr.fillStyle1 = (int) readUB(fillBits);
			}
			if (stateLineStyle) {
				scr.lineStyle = (int) readUB(lineBits);
			}
			if (stateNewStyles) {
				//scr.fillStyles = readFILLSTYLEARRAY(shapeNum);
				//scr.lineStyles = readLINESTYLEARRAY(shapeNum);

				scr.numFillBits = (int) readUB(4);
				scr.numLineBits = (int) readUB(4);
			}
			ret = scr;
		}
	} else {
		int straightFlag = (int) readUB(1);
		if (straightFlag == 1){

		} else {

		}
	}

	return ret;
}

vector<SHAPERECORD> DataStream::readSHAPERECORDS(int fillBits, int lineBits) {
	vector<SHAPERECORD> ret;
	SHAPERECORD rec;
	do {
		rec = readSHAPERECORD(fillBits, lineBits);
		if (dynamic_cast<StyleChangeRecord*>(&rec) != NULL) {
			/*
			if (rec.stateNewStyles) {
				fillBits = rec.numFillBits;
				lineBits = rec.numLineBits;
			}
			 */
		}
		ret.push_back(rec);
	} while (dynamic_cast<EndShapeRecord*>(&rec) == NULL);
	alignByte();

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
