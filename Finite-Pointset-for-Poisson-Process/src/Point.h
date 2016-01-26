/*
 * Point.h
 *
 *  Created on: Jan 22, 2015
 *      Author: saurabh
 */

#ifndef POINT_H_
#define POINT_H_

#include "Vector.h"
#include"math.h"

class Point {
	float coordinate_x;
	float coordinate_y;
	int bps;
	int box_number;
	int label;
	Vector<int> nbs;
	Vector<int> nbs_box;
	Vector<double> nbs_dist_x;
	Vector<double> nbs_dist_y;
	Vector<int> nbs_global_index;
	int number_of_neighbors;
	int global_index;
//	int compartment_number;
public:
	void set_Coordinate(float x, float y);
	float get_x_coordinate();
	float get_y_coordinate();
	void get_Point();
	void display();
	int getbps();
	void setbps(int );
	void set_nbs(int);
	void set_box_number(int );
	int get_box_number();
	void set_label(int );
	int get_label();
	int get_number_of_neighbors();
	void add_nbs(int ,int ,double, double ,int);
	void disp_nbs();
	void set_global_index(int );
	int get_global_index();
	double get_dist_x(int );
	double get_dist_y(int );
	int get_neighbour_global_index(int );
//	int get_compartment_number();
//	int set_compartment_number();


};

#endif /* POINT_H_ */
