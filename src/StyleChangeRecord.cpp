#include "StyleChangeRecord.h"

int StyleChangeRecord::changeX(int x) {
	if (stateMoveTo) {
		return moveDeltaX;
	}
	return x;
}

int StyleChangeRecord::changeY(int y) {
	if (stateMoveTo) {
		return moveDeltaY;
	}
	return y;
}
