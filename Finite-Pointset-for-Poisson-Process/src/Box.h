/*
 * Box.h
 *
 *  Created on: Apr 15, 2015
 *      Author: saurabh
 */

#ifndef BOX_H_
#define BOX_H_
#include "Vector.h"
#include"Point.h"

class Box {
	Vector<Point> points;
	float spacing;
	int number_of_elements;
	int box_1d;
	void add_neighbors(int ,int ,float );
	double calc_dist(double, double );
	double calc_dist_x(Point &, Point &);
	double calc_dist_y(Point &, Point &);
public:
	void initialize();
	void set_spacing(float);
	float get_spacing();
	void add_point(float , float, int ,float ,int ,int);
	int get_number_of_elements();
	void set_box_1d(int );
	int get_box_1d();
	void print_point_list(ofstream & );
	void add_nbs(Box &, int ,int , float );
	float point_x_coordinate(int );
	float point_y_coordinate(int );
	int get_number_of_neighbors(int );
	Point & get_point(int );

};

#endif /* BOX_H_ */
