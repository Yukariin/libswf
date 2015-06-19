#include "FILLSTYLE.h"
#include "RGBA.h"
#include "FOCALGRADIENT.h"

FILLSTYLE::FILLSTYLE() {
}

FILLSTYLE::FILLSTYLE(DataStream *ds, int shapeNum) {
	readData(ds, shapeNum);
}

void FILLSTYLE::readData(DataStream *ds, int shapeNum) {
	fillStyleType = ds->readUI8();
	if (fillStyleType == fillStyleTypes::SOLID) {
		if (shapeNum >= 3) {
			color = RGBA(ds);
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
		gradient = GRADIENT(ds, shapeNum);
	}
	if (fillStyleType ==fillStyleTypes::FOCAL_RADIAL_GRADIENT) {
		gradient = FOCALGRADIENT(ds, shapeNum);
	}

	if ((fillStyleType ==fillStyleTypes::REPEATING_BITMAP)
		|| (fillStyleType ==fillStyleTypes::CLIPPED_BITMAP)
		|| (fillStyleType ==fillStyleTypes::NON_SMOOTHED_REPEATING_BITMAP)
		|| (fillStyleType ==fillStyleTypes::NON_SMOOTHED_CLIPPED_BITMAP)) {
		bitmapId = ds->readUI16();
		bitmapMatrix = MATRIX(ds);
	}
}
