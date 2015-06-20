#ifndef LIBSWF_MULTINAMEINFO_H
#define LIBSWF_MULTINAMEINFO_H


#include <stdint.h>
#include <vector>

using namespace std;

class MultinameInfo {
public:
	uint8_t kind;
	enum multinameKinds {
		KIND_QNAME = 0x07,
		KIND_QNAMEA = 0x0D,
		KIND_RTQNAME = 0x0F,
		KIND_RTQNAMEA = 0x10,
		KIND_RTQNAMEL = 0x11,
		KIND_RTQNAMELA = 0x12,
		KIND_MULTINAME = 0x09,
		KIND_MULTINAMEA = 0x0E,
		KIND_MULTINAMEL = 0x1B,
		KIND_MULTINAMELA = 0x1C
	};
	vector<uint8_t> data;

	MultinameInfo();

	void readData();
};


#endif //LIBSWF_MULTINAMEINFO_H
