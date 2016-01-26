/*
 * Curve.cpp
 *
 *  Created on: May 14, 2015
 *      Author: saurabh
 */

#include "Curve.h"
#include "math.h"
#include <fstream>
void Curve::set_curve_length(Point & start, Point & end){
	curve_length = 1.0;
	Initial.setCoordinates(start.get_x_coordinate(),start.get_y_coordinate(),start.get_normal_x(),start.get_normal_y());
	End.setCoordinates(end.get_x_coordinate(),end.get_y_coordinate(),end.get_normal_x(),end.get_normal_y());
}
int Curve::get_number_of_segments(){
	return number_of_segments;
}
void Curve::set_number_of_segment(double h){
	alpha = 0.3;
	beeta = 0.8;
	smoothing_length = h;
	segment_length = 5*alpha*smoothing_length;
	number_of_segments = ceil(curve_length/segment_length);
}


void Curve::curve_fill(){
	segment = new Vector<Point>[number_of_segments];

//	Segments.set_size(number_of_segments);
	for(int i = 0; i < number_of_segments; i++){
		segment[i].set_size(5);
	}

}

void Curve::set_normal_x(){
	normal_x = Initial.get_normal_x();
//	cout << Initial.get_normal_x() << endl;
}

void Curve::set_normal_y(){
	normal_y = Initial.get_normal_y();
//	cout << Initial.get_normal_y() << endl;
}
int Curve::boundary_fill(){
	int dir,xd,yd;
	total_curve_point = 0;
	if(normal_x == 0){
//		cout << "entered";
		xd = 1;
		yd = 0;
		if(Initial.get_x_coordinate() < End.get_x_coordinate()){
			dir = 1;
		}
		else{
			dir = -1;
		}
	}
	if(normal_y == 0){
		xd = 0;
		yd = 1;
		if(Initial.get_y_coordinate() < End.get_y_coordinate()){
			dir = 1;

		}
		else{
			dir = -1;
		}
	}

	for(int i = 0; i < number_of_segments - 1; i++){

		double xx = Initial.get_x_coordinate() + (alpha*smoothing_length)*dir*xd*(5.0*i + 2.5);
		double yy = Initial.get_y_coordinate() + (alpha*smoothing_length)*dir*yd*(5.0*i + 2.5);
		segment[i][2].setCoordinates(xx,yy,normal_x,normal_y);
		total_curve_point++;
		xx = segment[i][2].get_x_coordinate() + (alpha*smoothing_length)*xd*dir;
    	yy = segment[i][2].get_y_coordinate() + (alpha*smoothing_length)*yd*dir;
		segment[i][3].setCoordinates(xx,yy,normal_x,normal_y);
		total_curve_point++;
		xx = segment[i][3].get_x_coordinate() + (alpha*smoothing_length)*xd*dir;
		yy = segment[i][3].get_y_coordinate() + (alpha*smoothing_length)*yd*dir;
		segment[i][4].setCoordinates(xx,yy,normal_x,normal_y);
		total_curve_point++;
		xx = segment[i][2].get_x_coordinate() - (alpha*smoothing_length)*xd*dir;
		yy = segment[i][2].get_y_coordinate() - (alpha*smoothing_length)*yd*dir;
		segment[i][1].setCoordinates(xx,yy,normal_x,normal_y);
		total_curve_point++;
		xx = segment[i][1].get_x_coordinate() - (alpha*smoothing_length)*xd*dir;
		yy = segment[i][1].get_y_coordinate() - (alpha*smoothing_length)*yd*dir;
		segment[i][0].setCoordinates(xx,yy,normal_x,normal_y);
		total_curve_point++;
	}
	segment[0][0].setCoordinates(Initial.get_x_coordinate(),Initial.get_y_coordinate(),normal_x,normal_y);
//	for(int i = 0; i < number_of_segments - 1; i++){
//		for(int j = 0; j < 5; j++){
//			fout << segment[i][j].get_x_coordinate() << "\t" << segment[i][j].get_y_coordinate() << endl;
//		}
//	}

	double xx = segment[number_of_segments - 2][4].get_x_coordinate();
	double yy = segment[number_of_segments - 2][4].get_y_coordinate();
	double end_x = End.get_x_coordinate();
	double end_y = End.get_y_coordinate();
	double dist = sqrt(((xx - end_x)*(xx - end_x)) + ((yy - end_y)*(yy - end_y)));
	last_segment_point = 0;
//	cout << "*************" << xx << "\t" << yy << dist<<endl;
	while(dist > beeta*smoothing_length){
		xx = xx + (alpha*smoothing_length)*xd*dir;
		yy = yy + (alpha*smoothing_length)*yd*dir;
		dist = sqrt(((xx - end_x)*(xx - end_x)) + ((yy - end_y)*(yy - end_y)));
		segment[number_of_segments - 1][last_segment_point].setCoordinates(xx,yy,normal_x,normal_y);
//		cout << xx << "\t" << yy << "\t" << dist << endl;
		last_segment_point++;
		total_curve_point++;
	}
//	cout << last_segment_point << endl;
//	total_curve_point += last_segment_point - 1;
//	int i = number_of_segments - 1;

//	for(int j = 0; j < last_segment_point; j++){
//			fout << segment[i][j].get_x_coordinate() << "\t" << segment[i][j].get_y_coordinate() << endl;
//	}
	return total_curve_point;
}

void Curve::get_point(Point & point, int j, int k){
	point.setCoordinates(segment[j][k].get_x_coordinate(),segment[j][k].get_y_coordinate(),segment[j][k].get_normal_x(),segment[j][k].get_normal_y());
}

int Curve::get_last_segment_point(){
	return last_segment_point;
}
