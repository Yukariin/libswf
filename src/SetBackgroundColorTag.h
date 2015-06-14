//
// Created by yukarin on 6/5/15.
//

#ifndef LIBSWF_SETBACKGROUNDCOLORTAG_H
#define LIBSWF_SETBACKGROUNDCOLORTAG_H


#include "Tag.h"
#include "RGB.h"

class SetBackgroundColorTag : public Tag {
public:
	uint16_t id = 9;

	RGB backgroundColor;

    SetBackgroundColorTag(DataStream* ds);
    void readData(DataStream* ds);
};


#endif //LIBSWF_SETBACKGROUNDCOLORTAG_H
