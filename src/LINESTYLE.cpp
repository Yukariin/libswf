#include "LINESTYLE.h"
#include "RGBA.h"

LINESTYLE::LINESTYLE() {

}

LINESTYLE::LINESTYLE(DataStream *ds, int shapeNum) {
	readData(ds, shapeNum);
}

void LINESTYLE::readData(DataStream *ds, int shapeNum) {
	width = ds->readUI16();
	if ((shapeNum == 1) || (shapeNum == 2)) {
		color = RGB(ds);
	}
	if (shapeNum == 3) {
		color = RGBA(ds);
	}
}
