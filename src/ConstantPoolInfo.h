#ifndef LIBSWF_CONSTANTPOOLINFO_H
#define LIBSWF_CONSTANTPOOLINFO_H


#include <vector>
#include <stdint.h>

class ConstantPoolInfo {
public:
	std::vector<int32_t> constant_int;
	std::vector<uint32_t> constant_uint;
	std::vector<double> constant_double;

	ConstantPoolInfo();

	void readData();
};



#endif //LIBSWF_CONSTANTPOOLINFO_H
