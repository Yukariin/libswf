#include "FileAttributesTag.h"

FileAttributesTag::FileAttributesTag(DataStream *ds) : Tag(ID, "FileAttributes") {
	readData(ds);
}

void FileAttributesTag::readData(DataStream *ds) {
	reserved1 = ds->readUB(1) == 1;
	useDirectBlit = ds->readUB(1) != 0;
	useGPU = ds->readUB(1) != 0;
	hasMetadata = ds->readUB(1) != 0;
	actionScript3 = ds->readUB(1) != 0;
	noCrossDomainCache = ds->readUB(1) != 0;
	reserved2 = ds->readUB(1) == 1;
	useNetwork = ds->readUB(1) != 0;
	reserved3 = (int)ds->readUB(24);
}
