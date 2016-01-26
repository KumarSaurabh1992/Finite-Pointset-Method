/*
 * Point.h
 *
 *  Created on: Jan 21, 2015
 *      Author: saurabh
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
	double coordinate_x;
	double coordinate_y;
	int normal_x;
	int normal_y;
public:
//	Point(float x,float y);
	virtual ~Point();
	void setCoordinates(double , double ,int , int );
	double get_x_coordinate();
	double get_y_coordinate();
	int get_normal_x();
	int get_normal_y();
	double calc_distance(Point &);
};

#endif /* POINT_H_ */
