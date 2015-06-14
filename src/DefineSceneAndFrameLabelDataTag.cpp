#include "DefineSceneAndFrameLabelDataTag.h"

DefineSceneAndFrameLabelDataTag::DefineSceneAndFrameLabelDataTag(DataStream *ds) {
    readData(ds);
}

void DefineSceneAndFrameLabelDataTag::readData(DataStream *ds) {
    uint32_t sceneCount = ds->readEncodedU32();
	for (int i = 0; i < sceneCount; i++) {
        sceneOffsets.push_back(ds->readEncodedU32());
        sceneNames.push_back(ds->readString());
	}

    uint32_t frameLabelCount = ds->readEncodedU32();
	for (int i = 0; i < frameLabelCount; i++) {
        frameNums.push_back(ds->readEncodedU32());
        frameNames.push_back(ds->readString());
	}
}
