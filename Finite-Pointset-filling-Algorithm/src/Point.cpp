/*
 * Point.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: saurabh
 */

#include "Point.h"
#include "math.h"
#include <iostream>
using namespace std;


void Point::setCoordinates(double x, double y, int nx, int ny){
	coordinate_x = x;
	coordinate_y = y;
	normal_x = nx;
	normal_y = ny;

}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

double Point::get_x_coordinate(){
	return coordinate_x;
}

double Point::get_y_coordinate(){
	return coordinate_y;
}

int Point::get_normal_x(){
	return normal_x;
}

int Point::get_normal_y(){
	return normal_y;
}

double Point::calc_distance(Point & point){
	double x_dist = point.get_x_coordinate() - coordinate_x;
	double y_dist = point.get_y_coordinate() - coordinate_y;
	double dist = sqrt(x_dist*x_dist + y_dist*y_dist);
	return dist;
}
