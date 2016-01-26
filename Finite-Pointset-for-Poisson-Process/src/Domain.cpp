/*
 * Domain.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: saurabh
 */

#include "Domain.h"
#include "SparseMatrix.h"
#include "IterativeSolver.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

void Domain::set_size(int m, int n){
	box.set_size(m,n);
}

int Domain::calculate_box_x(float x){
	int box_x = floor(x/smoothing_length);
	return box_x;

}

int Domain::calculate_box_y(float y){
	int box_y = floor(y/smoothing_length);
	return box_y;
}

void Domain::add_domain_point(float x, float y, int gl_ind){
	//	cout << gl_ind << endl;
	int bps = 0;
	if((fabs(y - 0.0) < pow(10.0,-6))){ //|| (fabs(x - 1.0) < pow(10.0,-6)) || (fabs(y - 0.0) < pow(10.0,-6)) || (fabs(y - 1.0) < pow(10.0,-6))){
		bps = 1;
	}
	else if((fabs(x - 1.0)) < pow(10.0,-6)){
		bps = 2;
	}
	else if((fabs(y - 1.0)) < pow(10.0,-6)){
		bps = 3;
	}
	else if((fabs(x - 0.0)) < pow(10.0,-6)){
		bps = 4;
	}
	number_of_points = gl_ind;
	int box_x = calculate_box_x(y);
	int box_y = calculate_box_y(x);
	int box_1d = box(box_x,box_y).get_box_1d();
	global_list_box[number_of_points] = box_1d;
	global_box_label[number_of_points] = box(box_x,box_y).get_number_of_elements();
	box(box_x,box_y).add_point(x,y,box_1d,smoothing_length,bps,gl_ind);

	if((box_x == 0) && (box_y == 0)){ // bottom left
		//		cout << "Case 1" << endl;
		box(box_x,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);

	}
	else if ((box_x == box.get_row_size() - 1) && (box_y == 0)){ // top left
		//		cout << "Case 2" << endl;
		box(box_x,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
	}
	else if ((box_x == box.get_row_size() - 1) && (box_y == box.get_column_size() - 1)){ // top right
		//		cout << "Case 3" << endl;
		box(box_x,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
	}
	else if ((box_x == 0) && (box_y == box.get_column_size() - 1)){ // bottom right
		//		cout << "Case 4" << endl;
		box(box_x,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
	}
	else if ((box_x == 0)){ // left face
		//		cout << "Case 5" << endl;
		box(box_x,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
	}
	else if ((box_y == box.get_column_size() - 1)){ // top face
		//		cout << "Case 6" << endl;
		box(box_x - 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
	}

	else if ((box_x == box.get_row_size() - 1)) { // right face
		//		cout << "Case 7" << endl;
		box(box_x ,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
	}
	else if ((box_y == 0)){ // bottom face
		//		cout << "Case 8" << endl;
		box(box_x - 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
	}
	else{
		//		cout << "Case 9" << endl;
		box(box_x - 1,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x - 1,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x ,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y + 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x + 1,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		box(box_x,box_y - 1).add_nbs(box(box_x,box_y),(box(box_x,box_y).get_number_of_elements() - 1),gl_ind,smoothing_length);
		//		cout << "reached " << endl;

	}




}

void Domain::get_boundary_condition(){
	alpha.set_size(4);
	beeta1.set_size(4);
	beeta2.set_size(4);
	gama.set_size(4);
	cout << "Enter the boundary condition" << endl;
	for(int i = 0; i < 4; i++){
		cin >> alpha[i];
		cin >> beeta1[i];
		cin >> beeta2[i];
		cin >> gama[i];
	}
}
void Domain::fill_domain(){
	//	ifstream fin;
	//
	//	fin.open("Points.txt");
	//	float x,y,temp;
	//	int gl_index = 0;
	//	if(fin.is_open()){
	//		while(!fin.eof()){
	//			for(int i = 0; i < 2; i++){
	//				if(i == 0){
	//					fin >> x;
	//				}
	//				else if(i == 1){
	//					fin >> y;
	//				}
	//				else{
	//					fin >> temp;
	//				}
	//
	//			}
	////			cout << x << "\t" << y << endl;
	//			add_domain_point(x,y,gl_index);
	//			gl_index++;
	//		}
	//	}
	//	cout << "Reached" << endl;
	//	fin.close();
	//	cout << "Reached" << endl;
	//		cout << "Line 45" << endl;
	float h = smoothing_length;
	float i = 0.0;
	float alpha1 = 0.3;
	float beta = 0.7;
	srand(time(NULL));
	float r;
	int gl_index = 0;
	while(i < fabs(1 - alpha1*h)){
		float j = 0.0;
		add_domain_point(j,i,gl_index);
		gl_index++;
		while(j < (1 - (beta*h))){
			r=alpha1*h+((float)rand()/(RAND_MAX))*(beta-alpha1)*h;
			j = j + r;
			if(j > (1 - alpha1*h)){
				float r1 = alpha1*h+((float)rand()/(RAND_MAX))*(beta-2*alpha1)*h;
				j = j + r1 - r;
			}
			add_domain_point(j,i,gl_index);
			gl_index++;
			//
		}
		add_domain_point(1,i,gl_index);
		gl_index++;
		r=alpha1*h+((float)rand()/(RAND_MAX))*(beta-alpha1)*h;
		i = i + r;
		if(i > fabs(1 - alpha1*h)){
			float r1 = alpha1*h+((float)rand()/(RAND_MAX))*(beta-2*alpha1)*h;
			i = i + r1 - r;
		}
	}

	i = 1;
	float j = 0;
	while(j < (1 - (beta*h))){
		r=alpha1*h+((float)rand()/(RAND_MAX))*(beta-alpha1)*h;
		j = j + r;
		if(j > (1 - alpha1*h)){
			float r1 = alpha1*h+((float)rand()/(RAND_MAX))*(beta-2*alpha1)*h;
			j = j + r1 - r;
		}
		add_domain_point(j,i,gl_index);
		gl_index++;

	}
	add_domain_point(1,i,gl_index);
	gl_index++;
	cout <<"Reached Here" << endl;
}

//void Domain::add_neighbor(int m,int n){
//	for(int i = 0; i < box(m,n).get_number_of_elements(); i++){
//		box()
//	}
//}

void Domain::write(){
	ofstream fout("Points2.txt");

	for(int i = 0; i < box.get_row_size(); i++){
		for(int j = 0; j < box.get_column_size(); j++){
			cout << "Box number : " << "(" << i << "," << j <<")" << "\t" << box(i,j).get_box_1d() << endl;
			box(i,j).print_point_list(fout);
		}
	}
	fout.close();


}


void Domain::initialize(){

	cout << "Enter the value of smoothing length" <<  endl;
	cin >> smoothing_length;
	int X = ceil(1.0/smoothing_length);
	int Y = ceil(1.0/smoothing_length);
	box.set_size(X,Y);
	int m = floor(1.0/(0.3*smoothing_length));
	global_list_box.set_size(m*m);
	global_box_label.set_size(m*m);
	for(int i = 0; i < X;i++){
		for(int j = 0; j < Y;j++){
			int id = i*Y + j;
			box(i,j).set_box_1d(id);
			box(i,j).initialize();


		}
	}
	get_boundary_condition();


}

double Domain::generate_random(double p ,double U){
	double alpha = 1.0/p;
	double beta = 1.0/(1.0 - p);
	if (U <= p){
		U = alpha*U;
	}
	else{
		U = beta*(U - p);
	}
	return U;
}

void Domain::createMatrix(){
	//	for(int i = 0; i < number_of_points; i++){
	//		int box_x = global_list[i]/10;
	//		int box_y = global_list[i] - box_x*10;
	//		cout <<i<<"\t"<< global_list[i] << "\t" << global_box_label[i] << "\t" << box(box_x,box_y).point_x_coordinate(global_box_label[i])<< "\t"<< box(box_x,box_y).point_y_coordinate(global_box_label[i]) << endl;
	//	}

	//	cout << "*************" << number_of_points << endl;
	array<double> M_inv;
	M_inv.set_size(6,6);
	Point p;
	SparseMatrix spm;
	//	cout << "Reached" << endl;
	spm.initialize(number_of_points + 1);
	cout << "Reached" << endl;
	Vector<double> B;
	B.set_size(number_of_points + 1);
	//	cout << "*************" << number_of_points << endl;
	for(int i = 0; i <= number_of_points; i++){
		//		cout << "Line 272 : Domain" << endl;
		int number_of_rows = ceil(1.0/smoothing_length);
		int box_x = global_list_box[i]/number_of_rows;
		//		if(box_x == 26){
		//			box_x = 25;
		//		}
		int box_y = global_list_box[i] - box_x*number_of_rows;
		//	int number_of_neighbors = box(box_x,box_y).get_number_of_neighbors(global_box_label[i]);

		//		cout << "Reached here"<< endl;

		//		cout << "Line 279 : Domain" << endl;
		//		cout << global_box_label.get_size() << endl;
		//		cout << i << endl;
		//		cout <<box_x << endl;
		//		cout << box_y << endl;
		//		cout << box.get_row_size() << endl;
		//		cout << box.get_column_size() << endl;
		//		cout << box(26,0).get_number_of_elements() << endl;

		p = box(box_x,box_y).get_point(global_box_label[i]);

		//		cout << "Line 280: Domain" << endl;
		array<double> M;
		array<double> W;
		array <double> M_trans;
		//			cout << i << endl;

		//	cout << number_of_neighbors<< endl;

		//			cout <<"Reached" << endl;
		int j;
		M.set_size(p.get_number_of_neighbors() + 1,6);
		W.set_size(p.get_number_of_neighbors() + 1, p.get_number_of_neighbors() + 1);
		M_trans.set_size(6,p.get_number_of_neighbors() + 1);
		W.zeros();
		//		cout << "Reached" << endl;
		cout << p.get_number_of_neighbors() << endl;
		cout << "Reached" << endl;
		for(j = 0; j < p.get_number_of_neighbors(); j++){
			M(j,0) = 1.0;
			M(j,1) = p.get_dist_x(j);
			M(j,2) = p.get_dist_y(j);
			M(j,3) = p.get_dist_x(j)*p.get_dist_x(j)/2.0;
			M(j,4) = p.get_dist_x(j)*p.get_dist_y(j);
			M(j,5) = p.get_dist_y(j)*p.get_dist_y(j)/2.0;
			double dist = p.get_dist_x(j)*p.get_dist_x(j) + p.get_dist_y(j)*p.get_dist_y(j);
			W(j,j) = exp(-6.25*dist/smoothing_length);
		}

		if(p.getbps() == 0){
			M(j,0) = 0;
			M(j,1) = 0;
			M(j,2) = 0;
			M(j,3) = 1;
			M(j,4) = 0;
			M(j,5) = 1;
			W(j,j) = 1;
		}
		else{

			M(j,0) = alpha[p.getbps() - 1];
			M(j,1) = beeta1[p.getbps() - 1];
			M(j,2) = beeta2[p.getbps() - 1];
			M(j,3) = 0;
			M(j,4) = 0;
			M(j,5) = 0;

			W(j,j) = 1;
		}
		//	M.display();
		//	W.display();
		cout << "Reached" << endl;
		M.transpose(M_trans);
		//	M_trans.display();
		array<double> res1,res2,res3,res4;
		res1.set_size(M_trans.get_row_size(),W.get_column_size());
		//	res1.zeros();
		M_trans.multiply(W,res1);
		//	cout << "***************" << endl;
		//	res1.display();
		res2.set_size(res1.get_row_size(),M.get_column_size());
		res2.zeros();
		res1.multiply(M,res2);
		res2.inverse_66(M_inv);
		cout << "Reached" << endl;
		//	M_inv.display();
		//		cout << "Line 339" << endl;
		res3.set_size(M_inv.get_row_size(),M_trans.get_column_size());
		res3.zeros();
		M_inv.multiply(M_trans,res3);
		res4.set_size(res3.get_row_size(),W.get_column_size());
		res4.zeros();
		res3.multiply(W,res4);
		if(p.getbps() == 0){
			B[i] = res4(0,p.get_number_of_neighbors())*(2);
		}
		else{
//			B[i] = res4(0,p.get_number_of_neighbors())*(0);
			if(p.getbps() == 1){
				B[i] = res4(0,p.get_number_of_neighbors())*(-gama[0]);
			}
			if(p.getbps() == 2){
				B[i] = res4(0,p.get_number_of_neighbors())*(-gama[1]);
			}
			if(p.getbps() == 3){
				B[i] = res4(0,p.get_number_of_neighbors())*(-gama[2]);
			}
			if(p.getbps() == 4){
				B[i] = res4(0,p.get_number_of_neighbors())*(-gama[3]);
			}
		}
		//	res4.display();
		//				cout << "Line 352" << endl;
		int lab = p.get_global_index();
		//		cout << lab << endl;
		int temp_ind = 0;
		//		if(i == 280){
		//			res4.display();
		//		}
		//		cout << "Line 360" << endl;
		for(int k = 0 ; k < p.get_number_of_neighbors(); k++){
			//			cout << "Line 352 " << endl;
			int nb_lab = p.get_neighbour_global_index(k);

			if((nb_lab > lab) && (temp_ind == 0)){
				//				cout << lab << "\t" << lab << endl;
				spm.update_matrix(-1.0,lab,lab);
				temp_ind = 1;

			}
			//				cout << lab << "\t" << nb_lab << endl;
			//			cout << "Line 372" << endl;
			spm.update_matrix(res4(0,k),lab,nb_lab);
			//			cout << "Line 374: Domain" << endl;

			//			cout << lab << endl;
		}

		if(temp_ind == 0){
			//			cout << lab << "\t" << lab << endl;
			//			cout << "Line 381 : Domain" << endl;
			spm.update_matrix(-1.0,lab,lab);
			//			cout << "Line 383: Domain" << endl;
		}



	}
	//	B.display();
	cout << "Reached" << endl;
	spm.resize_matrix();
	//		spm.write_file();
	cout << "Reached" << endl;
	Iterative_Solver its;
	Vector<double> X;
	X.set_size(B.get_size());
	its.BiCG(spm,X,B);
	cout << "Writing in file" << endl;
	ofstream fout("solver.txt");
	for(int i = 0; i < X.get_size(); i++){
		fout << X[i] << endl;
	}
	fout.close();

	fout.open("Point_fin.txt");
	for(int i = 0; i <= number_of_points; i++){
		//		cout << "Reached" << endl;
		int number_of_rows = ceil(1.0/smoothing_length);
		int box_x = global_list_box[i]/number_of_rows;
		int box_y = global_list_box[i] - box_x*number_of_rows;
		//	int number_of_neighbors = box(box_x,box_y).get_number_of_neighbors(global_box_label[i]);

		//		cout << "Reached here"<< endl;
		p = box(box_x,box_y).get_point(global_box_label[i]);
		fout << p.get_global_index() << "\t" << p.get_x_coordinate() << "\t" << p.get_y_coordinate() << endl;
	}
	fout.close();
	cout << "File Written" << endl;

}
