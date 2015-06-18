#include "MATRIX.h"

MATRIX::MATRIX() {

}

MATRIX::MATRIX(MATRIX *m) {
	if (!m) {
		return;
	}
	hasScale = m->hasScale;
	hasRotate = m->hasRotate;
	scaleX = m->scaleX;
	scaleY = m->scaleY;
	rotateSkew0 = m->rotateSkew0;
	rotateSkew1 = m->rotateSkew1;
	translateX = m->translateX;
	translateY = m->translateY;
}

MATRIX::MATRIX(DataStream *ds) {
	readData(ds);
}

void MATRIX::readData(DataStream *ds) {
	hasScale = ds->readUB(1) == 1;
	if (hasScale) {
		int NScaleBits = (int) ds->readUB(5);
		scaleX = (int) ds->readSB(NScaleBits);
		scaleY = (int) ds->readSB(NScaleBits);
		nScaleBits = NScaleBits;
	}
	hasRotate = ds->readUB(1) == 1;
	if (hasRotate) {
		int NRotateBits = (int) ds->readUB(5);
		rotateSkew0 = (int) ds->readSB(NRotateBits);
		rotateSkew1 = (int) ds->readSB(NRotateBits);
		nRotateBits = NRotateBits;
	}
	int NTranslateBits = (int) ds->readUB(5);
	translateX = (int) ds->readSB(NTranslateBits);
	translateY = (int) ds->readSB(NTranslateBits);
	nTranslateBits = NTranslateBits;
	ds->alignByte();
}
