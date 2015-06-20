#ifndef LIBSWF_DEFINESCENEANDFRAMELABELDATATAG_H
#define LIBSWF_DEFINESCENEANDFRAMELABELDATATAG_H


#include <string>
#include <vector>

#include "Tag.h"

using namespace std;

class DefineSceneAndFrameLabelDataTag : public Tag {
public:
	static const uint16_t ID = 86;

	vector<uint32_t> sceneOffsets;
	vector<string> sceneNames;

	vector<uint32_t> frameNums;
	vector<string> frameNames;

	DefineSceneAndFrameLabelDataTag(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_DEFINESCENEANDFRAMELABELDATATAG_H
