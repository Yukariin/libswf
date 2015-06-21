#ifndef LIBSWF_ZONEDATA_H
#define LIBSWF_ZONEDATA_H


#include "DataStream.h"

class ZONEDATA {
public:
	float alignmentCoordinate;
	float range;

	ZONEDATA(DataStream* ds);

	void readData(DataStream* ds);

	string toString();
};


#endif //LIBSWF_ZONEDATA_H
