#ifndef LIBSWF_TAG_H
#define LIBSWF_TAG_H


#include <stdint.h>
#include <string>

#include "DataStream.h"

using namespace std;

class Tag {
public:
	Tag(uint16_t tagId, string tagName);

	virtual void readData(DataStream* ds) = 0;

	uint16_t getId();
	virtual string getName();

protected:
	uint16_t id;
	string tagName;
};


#endif //LIBSWF_TAG_H
