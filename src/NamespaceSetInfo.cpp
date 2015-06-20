#include "NamespaceSetInfo.h"

NamespaceSetInfo::NamespaceSetInfo() {
}

NamespaceSetInfo::NamespaceSetInfo(vector<uint32_t> ns) {
	this->ns = ns;
}

void NamespaceSetInfo::readData() {
	// TODO: read u30 count
	// TODO: read ns
}
