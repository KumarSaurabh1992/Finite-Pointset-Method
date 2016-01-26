/*
 * Domain.h
 *
 *  Created on: Apr 15, 2015
 *      Author: saurabh
 */

#ifndef DOMAIN_H_
#define DOMAIN_H_
#include "Box.h"
#include "array.h"

class Domain {
	array<Box> box;
	float smoothing_length;
	Vector<int> global_list_box;
	Vector<int> global_box_label;
	int number_of_points;
	Vector<float> alpha;
	Vector<float> beeta1;
	Vector<float> beeta2;
	Vector<float> gama;

public:
	void get_boundary_condition();
	void set_size(int, int);
	void fill_domain();
	void write();
	int calculate_box_x(float );
	int calculate_box_y(float );
	void initialize();
	void add_domain_point(float, float, int);
	void add_neighbor(int , int);
	double generate_random(double, double);
	void createMatrix();

};

#endif /* DOMAIN_H_ */
