#include "RGBA.h"

RGBA::RGBA(DataStream *ds) {
	readData(ds);
}

RGBA::RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : RGB(red, green, blue)
{
	this->alpha = alpha;
}

RGBA::RGBA(RGBA *r) {
	red = r->red;
	green = r->green;
	blue = r->blue;
	alpha = r->alpha;
}

void RGBA::readData(DataStream *ds) {
	red = ds->readUI8();
	green = ds->readUI8();
	blue = ds->readUI8();
	alpha = ds->readUI8();
}
