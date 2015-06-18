#ifndef LIBSWF_GRADIENT_H
#define LIBSWF_GRADIENT_H


#include <vector>

#include "DataStream.h"
#include "GRADRECORD.h"

class GRADIENT {
public:
	int spreadMode;
	enum spreadModes {
		SPREAD_PAD_MODE = 0,
		SPREAD_REFLECT_MODE = 1,
		SPREAD_REPEAT_MODE = 2,
		SPREAD_RESERVED = 3
	};

	int interpolationMode;
	enum interpolationModes {
		INTERPOLATION_RGB_MODE = 0,
		INTERPOLATION_LINEAR_RGB_MODE = 1,
		INTERPOLATION_RESERVED1 = 2,
		INTERPOLATION_RESERVED2 = 3
	};

	std::vector<GRADRECORD> gradientRecords;

	GRADIENT();
	GRADIENT(DataStream* ds);

	void readData(DataStream* ds);
};


#endif //LIBSWF_GRADIENT_H
