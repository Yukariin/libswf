#ifndef LIBSWF_FILEATTRIBUTESTAG_H
#define LIBSWF_FILEATTRIBUTESTAG_H


#include "Tag.h"

class FileAttributesTag : public Tag {
public:
	static const uint16_t ID = 69;

	bool reserved1;
	bool useDirectBlit;
	bool useGPU;
	bool hasMetadata;
	bool actionScript3;
	bool noCrossDomainCache;
	bool reserved2;
	bool useNetwork;
	int reserved3;

	FileAttributesTag(DataStream* ds);
	void readData(DataStream* ds);
};


#endif //LIBSWF_FILEATTRIBUTESTAG_H
