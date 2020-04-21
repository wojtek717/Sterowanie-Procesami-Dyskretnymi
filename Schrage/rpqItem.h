#pragma once
#include <iostream>

class rpqItem
{

public:
	int r;
	int p;
	int q;
	int ordinalNumber;

	rpqItem(int r, int p, int q, int oN) {
		this->r = r;
		this->p = p;
		this->q = q;
		ordinalNumber = oN;
	}

	void printRPQ();

};

