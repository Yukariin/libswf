//
// Created by yukarin on 5/30/15.
//

#include "RECT.h"

RECT::RECT() {
}

RECT::RECT(int64_t Xmin, int64_t Xmax, int64_t Ymin, int64_t Ymax) {
	this->Xmin = Xmin;
	this->Xmax = Xmax;
	this->Ymin = Ymin;
	this->Ymax = Ymax;
}

RECT::RECT(RECT *r) {
	Xmin = r->Xmin;
	Xmax = r->Xmax;
	Ymin = r->Ymin;
	Ymax = r->Ymax;
}
