/*
 * Domain.h
 *
 *  Created on: May 15, 2015
 *      Author: saurabh
 */

#ifndef DOMAIN_H_
#define DOMAIN_H_
#include "Curve.h"
#include <fstream>
class Domain {
	Vector <Curve> cv;
	Vector <Point> p;
	Vector <Point> q;
	Vector<int> rol;
	int total_points;
	float alpha;
	float beeta;
	float smoothing_length;
public:
	void Boundary_fill(float );
//	void neighbour_search();
	void Domain_fill(float );
};

#endif /* DOMAIN_H_ */
