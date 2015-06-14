//
// Created by yukarin on 6/2/15.
//

#ifndef LIBSWF_FILEATTRIBUTESTAG_H
#define LIBSWF_FILEATTRIBUTESTAG_H


#include "Tag.h"

class FileAttributesTag : public Tag {
public:
	uint16_t id = 69;

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
