#ifndef LIBSWF_SYMBOLCLASSTAG_H
#define LIBSWF_SYMBOLCLASSTAG_H


#include "Tag.h"

class SymbolClassTag : public Tag {
public:
	static const uint16_t ID = 76;

	vector<uint16_t > tags;
	vector<string> names;

	SymbolClassTag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_SYMBOLCLASSTAG_H
