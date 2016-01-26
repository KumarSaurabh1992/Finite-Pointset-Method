/*
 * Point.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: saurabh
 */

#include "Point.h"
#include <iostream>
using namespace std;


void Point::set_Coordinate(float x, float y){
	coordinate_x = x;
	coordinate_y = y;

}

float Point::get_x_coordinate(){
	return coordinate_x;
}

float Point::get_y_coordinate(){
	return coordinate_y;
}

void Point::get_Point(){
	float x,y;
	cout << "Enter the coordinates";
	cin >> x;
	cin >> y;
	set_Coordinate(x,y);
}

void Point::display(){
	cout << "(" << get_x_coordinate() << ", " << get_y_coordinate() << ")";
}

void Point::setbps(int x){
	bps = x;
}

int Point::getbps(){
	return bps;
}

void Point::set_nbs(int m){
	nbs.set_size(m);
	nbs_box.set_size(m);
	nbs_dist_x.set_size(m);
	nbs_dist_y.set_size(m);
	number_of_neighbors = 0;
}

int Point::get_number_of_neighbors(){
	return number_of_neighbors;
}

void Point::set_box_number(int x){
	box_number = x;
}

int Point::get_box_number(){
	return box_number;
}

void Point::set_label(int x){
	label = x;
}

int Point::get_label(){
	return label;
}

void Point::add_nbs(int lab, int box1d, double dist_x, double dist_y,int gl_index){
	int i = number_of_neighbors - 1;
//	if(global_index == 52){
//		cout << gl_index << endl;
//	}
	while((gl_index < nbs_global_index[i]) && (i >= 0)){
		nbs[i + 1] = nbs[i];
		nbs_box[i + 1] = nbs_box[i];
		nbs_dist_x[i + 1] = nbs_dist_x[i];
		nbs_dist_y[i + 1] = nbs_dist_y[i];
		nbs_global_index[i + 1] = nbs_global_index[i];
		i--;
	}


	nbs[i + 1] = lab;
	nbs_box[i + 1] = box1d;
	nbs_dist_x[i + 1] = dist_x;
	nbs_dist_y[i + 1] = dist_y;
	nbs_global_index[i + 1] = gl_index;
	number_of_neighbors++;
}

void Point::disp_nbs(){
	for(int i = 0; i < number_of_neighbors; i++){
		double dist = sqrt(nbs_dist_x[i]*nbs_dist_x[i] + nbs_dist_y[i]*nbs_dist_y[i]);
		cout << nbs[i] <<  "\t" << nbs_box[i] << "\t"   <<  nbs_global_index[i]  <<"\t" << dist << endl ;
		if(dist > 0.4){
			cout <<"***************************************************Wrong***********" << endl;
		}
	}
}

void Point::set_global_index(int ind){
	global_index = ind;
}

int Point::get_global_index(){
	return global_index;

}

double Point::get_dist_x(int lab){
	return nbs_dist_x[lab];
}

double Point::get_dist_y(int lab){
	return nbs_dist_y[lab];
}

int Point::get_neighbour_global_index(int lab){
	return nbs_global_index[lab];
}
