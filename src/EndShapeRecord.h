#ifndef LIBSWF_ENDSHAPERECORD_H
#define LIBSWF_ENDSHAPERECORD_H


#include "SHAPERECORD.h"

class EndShapeRecord : public SHAPERECORD {
public:
	void readData(DataStream* ds);

	int changeX(int x);
	int changeY(int y);
};


#endif //LIBSWF_ENDSHAPERECORD_H
