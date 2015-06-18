#include "FILLSTYLE.h"

FILLSTYLE::FILLSTYLE() {
}

FILLSTYLE::FILLSTYLE(DataStream *ds) {
	readData(ds);
}

void FILLSTYLE::readData(DataStream *ds) {
	fillStyleType = ds->readUI8();
	if (fillStyleType == fillStyleTypes::SOLID) {
		if (shapeNum >= 3) {
			color = readRGBA();
		} else {
			color = RGB(ds);
		}
	}
	if ((fillStyleType ==fillStyleTypes::LINEAR_GRADIENT)
		|| (fillStyleType ==fillStyleTypes::RADIAL_GRADIENT)
		|| (fillStyleType ==fillStyleTypes::FOCAL_RADIAL_GRADIENT)) {
		gradientMatrix = MATRIX(ds);
	}
	if ((fillStyleType ==fillStyleTypes::LINEAR_GRADIENT)
		|| (fillStyleType ==fillStyleTypes::RADIAL_GRADIENT)) {
		gradient = readGRADIENT(shapeNum);
	}
	if (fillStyleType ==fillStyleTypes::FOCAL_RADIAL_GRADIENT) {
		gradient = readFOCALGRADIENT(shapeNum);
	}

	if ((fillStyleType ==fillStyleTypes::REPEATING_BITMAP)
		|| (fillStyleType ==fillStyleTypes::CLIPPED_BITMAP)
		|| (fillStyleType ==fillStyleTypes::NON_SMOOTHED_REPEATING_BITMAP)
		|| (fillStyleType ==fillStyleTypes::NON_SMOOTHED_CLIPPED_BITMAP)) {
		bitmapId = ds->readUI16();
		bitmapMatrix = MATRIX(ds);
	}
}
