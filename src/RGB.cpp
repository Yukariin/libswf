#include "RGB.h"

RGB::RGB() {

}

RGB::RGB(uint8_t red, uint8_t green, uint8_t blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
}

RGB::RGB(RGB &r) {
	red = r.red;
	green = r.green;
	blue = r.blue;
}

RGB::RGB(DataStream *ds) {
	readData(ds);
}

void RGB::readData(DataStream *ds) {
	red = ds->readUI8();
	green = ds->readUI8();
	blue = ds->readUI8();
}
