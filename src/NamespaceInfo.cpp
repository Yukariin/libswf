#include "NamespaceInfo.h"

NamespaceInfo::NamespaceInfo() {
}

NamespaceInfo::NamespaceInfo(uint8_t kind, uint32_t name) {
	this->kind = kind;
	this->name = name;
}

void NamespaceInfo::readData() {
	//TODO: read kind
	//TODO: read name
}
