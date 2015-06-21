#ifndef LIBSWF_ZONERECORD_H
#define LIBSWF_ZONERECORD_H


#include <vector>
#include <stdint.h>

#include "DataStream.h"
#include "ZONEDATA.h"

using namespace std;

class ZONERECORD {
public:
	vector<ZONEDATA> zonedata;
	bool reserved;
	bool zoneMaskX;
	bool zoneMaskY;

	ZONERECORD(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_ZONERECORD_H
