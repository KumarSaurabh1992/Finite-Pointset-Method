//============================================================================
// Name        : Fill.cpp
// Author      : saurabh
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Curve.h"
#include "Domain.h"
using namespace std;

int main() {
	Domain dmn;
	float h;
	cout << "Enter the smoothing length" << endl;
	cin >> h;
	dmn.Domain_fill(h);
	return 0;
}
