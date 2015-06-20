#include "Tag.h"

Tag::Tag(uint16_t tagId, string tagName) {
	this->id = tagId;
	this->tagName = tagName;
}

uint16_t Tag::getId() {
	return id;
}

string Tag::getName() {
	return tagName;
}
