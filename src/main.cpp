#include <iostream>
#include <fstream>
#include <assert.h>
#include <iterator>

#include "Swf.h"

using namespace std;

int main() {
	ifstream inputFile ("/home/yukarin/Yukariin.github.io/font/font.swf", ios::binary);
	assert(inputFile);
	inputFile.unsetf(ios::skipws);

	istream_iterator<uint8_t> b(inputFile), e;
	const vector<uint8_t> data(b, e);

	Swf swf(data);

	return 0;
}
