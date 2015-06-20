#ifndef LIBSWF_ABC_H
#define LIBSWF_ABC_H


#include <stdint.h>
#include <vector>

#include "ConstantPoolInfo.h"
#include "MethodInfo.h"
#include "MetadataInfo.h"
#include "InstanceInfo.h"
#include "ClassInfo.h"
#include "ScriptInfo.h"
#include "MethodBodyInfo.h"

using namespace std;

class ABC {
public:
	uint16_t major_version = 46;
	uint16_t minor_version = 16;
	ConstantPoolInfo constant_pool;
	vector<MethodInfo> method_info;
	vector<MetadataInfo> metadata_info;
	vector<InstanceInfo> instance_info;
	vector<ClassInfo> class_info;
	vector<ScriptInfo> script_info;
	vector<MethodBodyInfo> method_body_info;

	ABC();

	void readData();
};


#endif //LIBSWF_ABC_H
