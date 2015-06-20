#ifndef LIBSWF_TAG_H
#define LIBSWF_TAG_H


#include <stdint.h>

#include "DataStream.h"

class Tag {
public:
	uint16_t id;
	string tagName;

	Tag(uint16_t tagId, string tagName);

	virtual void readData(DataStream* ds) = 0;
};


#endif //LIBSWF_TAG_H
