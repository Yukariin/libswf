#include "DoABCDefineTag.h"

DoABCDefineTag::DoABCDefineTag(DataStream *ds) : Tag(ID, "DoABCDefine"){
	readData(ds);
}

void DoABCDefineTag::readData(DataStream *ds) {
	flags = ds->readUI32();
	name = ds->readString();
	abcData = ABC();
}
