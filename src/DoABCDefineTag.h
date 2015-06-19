#ifndef LIBSWF_DOABCDEFINETAG_H
#define LIBSWF_DOABCDEFINETAG_H


#include "Tag.h"
#include "ABC.h"

class DoABCDefineTag : public Tag {
public:
	uint16_t id = 82;

	uint32_t flags;
	string name;

	DoABCDefineTag(DataStream* ds);

	void readData(DataStream* ds);

private:
	ABC abcData;
};


#endif //LIBSWF_DOABCDEFINETAG_H
