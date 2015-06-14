//
// Created by yukarin on 5/12/15.
//

#ifndef LIBSWF_TAG_H
#define LIBSWF_TAG_H


#include <stdint.h>
#include "DataStream.h"

class Tag {
public:
    virtual void readData(DataStream* ds);
    uint16_t id;
	uint32_t length;
};


#endif //LIBSWF_TAG_H
