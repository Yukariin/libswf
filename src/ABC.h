#ifndef LIBSWF_ABC_H
#define LIBSWF_ABC_H


#include <stdint.h>

#include "ConstantPoolInfo.h"
#include "MethodInfo.h"
#include "MetadataInfo.h"
#include "InstanceInfo.h"
#include "ClassInfo.h"
#include "ScriptInfo.h"
#include "MethodBodyInfo.h"

class ABC {
public:
	uint16_t major_version = 46;
	uint16_t minor_version = 16;
	ConstantPoolInfo constant_pool;
	std::vector<MethodInfo> method_info;
	std::vector<MetadataInfo> metadata_info;
	std::vector<InstanceInfo> instance_info;
	std::vector<ClassInfo> class_info;
	std::vector<ScriptInfo> script_info;
	std::vector<MethodBodyInfo> method_body_info;

	ABC();

	void readData();
};


#endif //LIBSWF_ABC_H
