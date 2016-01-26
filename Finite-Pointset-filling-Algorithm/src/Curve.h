/*
 * Curve.h
 *
 *  Created on: May 14, 2015
 *      Author: saurabh
 */

#ifndef CURVE_H_
#define CURVE_H_
#define MAX_PTS 5
#include "Point.h"
#include "Vector.h"

class Curve {
	int number_of_segments;
	double curve_length;
	double segment_length;
	float alpha;
	float beeta;
	int normal_x;
	int normal_y;
	double smoothing_length;
	Vector<Point> * segment;
	Point Initial;
	Point End;
	int last_segment_point;
	int total_curve_point;

public:
	int get_number_of_segments();
	int get_curve_length();
	void set_number_of_segment(double );
	void set_curve_length(Point & ,Point & );
	void curve_fill();
	int boundary_fill();
	void set_normal_x();
	void set_normal_y();
	double segment_get_x();
	void get_point(Point &,int , int);
	int get_last_segment_point();


};

#endif /* CURVE_H_ */
