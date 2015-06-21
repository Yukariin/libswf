#include <iostream>
#include "SwfParser.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc > 1) {
		SwfParser p;
		p.readFromFile(argv[1]);
	}

	return 0;
}
