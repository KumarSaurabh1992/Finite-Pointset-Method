/*
 * Box.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: saurabh
 */

#include "Box.h"
#include "array.h"

#include "math.h"
#include <fstream>
void Box::set_spacing(float x){
	spacing = x;
}

float Box::get_spacing(){
	return spacing;
}

void Box::initialize(){
	number_of_elements = 0;
	points.set_size(35);
	for(int i = 0; i < 35; i++){
			points[i].set_nbs(31);
	}
}

void Box::set_box_1d(int id){
	box_1d = id;
}

int Box::get_box_1d(){
	return box_1d;
}

int Box::get_number_of_elements(){
	return number_of_elements;
}

void Box::add_point(float x, float y, int box1d ,float sm_length, int boundary,int gl_ind){
	points[number_of_elements].set_Coordinate(x,y);
	points[number_of_elements].set_label(number_of_elements);
	points[number_of_elements].set_box_number(box1d);
	points[number_of_elements].setbps(boundary);
	points[number_of_elements].set_global_index(gl_ind);

	add_neighbors(number_of_elements,gl_ind,sm_length);
	number_of_elements++;
}

void Box::add_neighbors(int lab, int gl_index,float sm_length){
//	cout << number_of_elements << endl;
	for(int i = 0; i < number_of_elements; i++){
		double dist, dist_x, dist_y;
		if(lab != i){
			dist_x = calc_dist_x(points[i],points[lab]);
			dist_y = calc_dist_y(points[i],points[lab]);
			dist = calc_dist(dist_x,dist_y);
			if(dist < sm_length){
				points[i].add_nbs(lab,box_1d,-dist_x,-dist_y,gl_index);
				points[lab].add_nbs(i,box_1d,dist_x,dist_y,points[i].get_global_index());
			}


		}
	}
}

double Box::calc_dist_x(Point & p1, Point &p2){
	double dist_x = (p1.get_x_coordinate() - p2.get_x_coordinate());
	return dist_x;
}

double Box::calc_dist_y(Point & p1, Point &p2){
	double dist_y = (p1.get_y_coordinate() - p2.get_y_coordinate());
	return dist_y;
}

double Box::calc_dist(double dist_x, double dist_y){
	double dist = sqrt((dist_x*dist_x) + (dist_y*dist_y));
	return dist;
}

void Box::print_point_list(ofstream & fout){
	for(int i = 0; i < number_of_elements; i++){
		cout << "Point = ";
		points[i].display();
		cout <<"\t" << points[i].get_global_index();
//		cout << points[i].get_x_coordinate() << "\t" << points[i].get_y_coordinate() << endl;
		cout << endl;
		cout << "Neighbors are" << endl;
		points[i].disp_nbs();
	}




		for(int i = 0; i < number_of_elements; i++){
			fout << points[i].get_global_index() <<"\t" << points[i].get_x_coordinate() << "\t" << points[i].get_y_coordinate() <<  endl;
		}


}


void Box::add_nbs(Box & b1,int lab,int gl_index, float sm_length){
	double dist,dist_x,dist_y;
	for(int i = 0; i < number_of_elements; i++){
		dist_x = calc_dist_x(b1.points[lab],points[i]);
		dist_y = calc_dist_y(b1.points[lab],points[i]);
		dist = calc_dist(dist_x,dist_y);
//		cout << "Line 86 box.cpp" << endl;
//		cout << points[i].get_number_of_neighbors() << endl;
		if(dist < sm_length){
//			cout << "Line 88 box.cpp " << endl;
			points[i].add_nbs(lab,b1.get_box_1d(),dist_x,dist_y,gl_index);
			b1.points[lab].add_nbs(points[i].get_label(),box_1d,-dist_x,-dist_y,points[i].get_global_index());
		}

	}
}

float Box::point_x_coordinate(int lab){
	return points[lab].get_x_coordinate();

}

float Box::point_y_coordinate(int lab){
	return points[lab].get_y_coordinate();
}

int Box::get_number_of_neighbors(int lab){
	return points[lab].get_number_of_neighbors();
}

Point & Box::get_point(int lab){
//	cout << points.get_size() << endl;
//	cout << lab << endl;
	return points[lab];
}
