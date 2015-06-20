//
// Created by yukarin on 5/12/15.
//

#include "EndTag.h"

EndTag::EndTag(DataStream *ds) : Tag(ID, "End") {
    readData(ds);
}

void EndTag::readData(DataStream *ds) {

}
