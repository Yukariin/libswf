#ifndef LIBSWF_ENDTAG_H
#define LIBSWF_ENDTAG_H


#include "Tag.h"

using namespace std;

class EndTag : public Tag {
public:
	static const uint16_t ID = 0;

	EndTag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_ENDTAG_H
