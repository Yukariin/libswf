#ifndef LIBSWF_UNKNOWNTAG_H
#define LIBSWF_UNKNOWNTAG_H


#include "Tag.h"

class UnknownTag : public Tag {
public:
	UnknownTag(uint16_t tagId);

	void readData(DataStream* ds);

	string getName();
};


#endif //LIBSWF_UNKNOWNTAG_H
