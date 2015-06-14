#ifndef LIBSWF_ENDTAG_H
#define LIBSWF_ENDTAG_H


#include "Tag.h"

using namespace std;

class EndTag : public Tag {
public:
    uint16_t id = 0;

    EndTag(DataStream* ds);

    void readData(DataStream* ds);
};


#endif //LIBSWF_ENDTAG_H
