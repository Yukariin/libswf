#ifndef LIBSWF_NAMESPACESETINFO_H
#define LIBSWF_NAMESPACESETINFO_H


#include <vector>
#include <stdint.h>

using namespace std;

class NamespaceSetInfo {
public:
	vector<uint32_t> ns;

	NamespaceSetInfo();
	NamespaceSetInfo(vector<uint32_t> ns);

	void readData();
};


#endif //LIBSWF_NAMESPACESETINFO_H
