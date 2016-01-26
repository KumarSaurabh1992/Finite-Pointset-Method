/*
 * Domain.cpp
 *
 *  Created on: May 15, 2015
 *      Author: saurabh
 */

#include "Domain.h"
#include <stdlib.h>
#include <time.h>

void Domain::Boundary_fill(float h){
	//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	total_points = 0;
	alpha = 0.3;
	beeta = 0.7;
	cv.set_size(4);
	//	Curve cv;

	smoothing_length = h;
	Point start,end;

	start.setCoordinates(0.0,0.0,0,-1);
	end.setCoordinates(1.0,0.0,0,-1);
	cv[0].set_curve_length(start,end);
	cv[0].set_number_of_segment(h);
	cv[0].curve_fill();
	cv[0].set_normal_x();
	cv[0].set_normal_y();
	total_points += cv[0].boundary_fill();

	start.setCoordinates(1.0,0.0,1,0);
	end.setCoordinates(1.0,1.0,1,0);
	cv[1].set_curve_length(start,end);
	cv[1].set_number_of_segment(h);
	cv[1].curve_fill();
	cv[1].set_normal_x();
	cv[1].set_normal_y();
	total_points +=cv[1].boundary_fill();

	start.setCoordinates(1.0,1.0,0,1);
	end.setCoordinates(0.0,1.0,0,1);
	cv[2].set_curve_length(start,end);
	cv[2].set_number_of_segment(h);
	cv[2].curve_fill();
	cv[2].set_normal_x();
	cv[2].set_normal_y();
	total_points +=cv[2].boundary_fill();

	start.setCoordinates(0.0,1.0,-1,0);
	end.setCoordinates(0.0,0.0,-1,0);
	cv[3].set_curve_length(start,end);
	cv[3].set_number_of_segment(h);
	cv[3].curve_fill();
	cv[3].set_normal_x();
	cv[3].set_normal_y();
	total_points +=cv[3].boundary_fill();


}

void Domain::Domain_fill(float h){
	ofstream fout("Points.txt");
	Boundary_fill(h);
	p.set_size(total_points);
	int label = 0;
	//	cout << total_points << endl;
	int count = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < cv[i].get_number_of_segments() - 1; j++){
			for(int k = 0; k < 5; k++){
				cv[i].get_point(p[count],j,k);
				count++;
			}
		}
		//		cout << "Reached " << endl;
		int j = cv[i].get_number_of_segments() - 1;
		//		cout << j << endl;
		for(int k = 0; k < cv[i].get_last_segment_point();k++){
			//			cout << j << k << endl;
			cv[i].get_point(p[count],j,k);
			count++;
		}
	}
	for(int i = 0; i < total_points;i++){
		fout << p[i].get_x_coordinate() << "\t" <<p[i].get_y_coordinate() << "\t" << p[i].get_normal_x()<< "\t" << p[i].get_normal_y() << "\t" << label<<endl;
	}

	q.set_size(total_points);
	rol.set_size(total_points);
	double xx,yy;
	int nxx,nyy;
	int sum = total_points;
	srand(time(NULL));
	while(sum > 5){
//	for(int time = 0; time < 10; time++){
	for(int i = 0; i < sum - 1; i++){
		double r=alpha*smoothing_length+((float)rand()/(RAND_MAX))*(beeta-2.0*alpha)*smoothing_length;
		xx = ((p[i].get_x_coordinate() + p[i+1].get_x_coordinate())/2) - ((p[i].get_normal_x()+p[i+1].get_normal_x())/2)*r;
		yy = ((p[i].get_y_coordinate() + p[i+1].get_y_coordinate())/2) - ((p[i].get_normal_y()+p[i+1].get_normal_y())/2)*r;
		nxx = p[i].get_normal_x();
		nyy = p[i].get_normal_y();
		q[i].setCoordinates(xx,yy,nxx,nyy);
//		fout << q[i].get_x_coordinate() << "\t" <<q[i].get_y_coordinate() << "\t" << q[i].get_normal_x() << "\t" << q[i].get_normal_y() << endl;
		rol[i] = 1;
	}
	// Add the last point
	double dist = q[sum-2].calc_distance(q[0]);
	if(dist > beeta*smoothing_length) {
		xx = ((q[sum-2].get_x_coordinate() + q[0].get_x_coordinate())/2);
		yy = ((q[sum-2].get_y_coordinate() + q[0].get_y_coordinate())/2);
		nxx = q[sum-2].get_normal_x();
		nyy = q[sum-2].get_normal_y();
		q[sum-1].setCoordinates(xx,yy,nxx,nyy);
		rol[sum-1] = 1;
	}else{
		sum = sum -1;
	}
	for(int i=0; i<sum-1; i++){
		dist = q[i].calc_distance(q[i+1]);
		if(dist<alpha*smoothing_length){
			xx = ((q[i].get_x_coordinate() + q[i+1].get_x_coordinate())/2);
			yy = ((q[i].get_y_coordinate() + q[i+1].get_y_coordinate())/2);
			nxx = q[i].get_normal_x();
			nyy = q[i].get_normal_y();
			q[i].setCoordinates(xx,yy,nxx,nyy);
			rol[i+1] = 0;
			i++;
		}
	}
	if(rol[sum-2]>0&&rol[sum-1]>0){
				dist = q[sum-2].calc_distance(q[sum-1]);
				if(dist<alpha*smoothing_length){
					xx = ((q[sum-2].get_x_coordinate() + q[sum-1].get_x_coordinate())/2);
		    		yy = ((q[sum-2].get_y_coordinate() + q[sum-1].get_y_coordinate())/2);
	    			nxx = q[sum-2].get_normal_x();
	    			nyy = q[sum-2].get_normal_y();
	    			q[sum-2].setCoordinates(xx,yy,nxx,nyy);
	    			rol[sum-1] = 0;
				}
			}
	double check;
			for(int i=0; i<sum; i++){
				for(int j=sum ; j>-1; j--){
					check = q[i].calc_distance(q[j]);
					if(rol[i]>0 && rol[j]>0 && i!=j && check<alpha*smoothing_length){
						rol[j]=0;
					}
				}
			}
			for(int i=0; i<sum; i++){
				for(int j=sum + 1; j>-1; j--){
					check = p[j].calc_distance(q[i]);
					if(rol[i]>0 && check<alpha*smoothing_length){
						rol[i]=0;
					}
				}
			}
			int sum1 = 0;

			label++;
			p.del();
			p.set_size(sum);
			for(int i = 0; i < sum; i++){
				if(rol[i] == 1){
					p[sum1].setCoordinates(q[i].get_x_coordinate(),q[i].get_y_coordinate(),q[i].get_normal_x(),q[i].get_normal_y());

					fout << p[sum1].get_x_coordinate() << "\t" << p[sum1].get_y_coordinate() << "\t" <<p[sum1].get_normal_x() << "\t"<<p[sum1].get_normal_y()<< "\t" << label <<endl;
					sum1++;
				}
			}
			total_points += sum1;
			sum = sum1;
			p.resize(sum);
			cout << sum1 << endl;
	}




}
