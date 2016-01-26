/*
 * array.h
 *
 *  Created on: Jan 16, 2015
 *      Author: saurabh
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include "Vector.h"
#include <iostream>
using namespace std;

template <class T> class array {
	int row,column;
	T **A;
	void getData();
	void initialize();
public:
	array<T>();
	array<T>(int m,int n);
	~array<T>();
	void display();
	void read_values();
	int get_row_size();
	int get_column_size();
	array operator + (array);
	array operator - (array);
	array operator * (array);
	T & operator() (int, int);
	array add(array);
	void set_size(int , int );
	void transpose(array<T> & arr);
	void multiply(array<T> & arr, array<T> & result);
	void multiply(Vector<T> & vec, Vector<T> & result);
	void inverse_66(array<T> &result);
	void zeros();
	void copy(array<T> &);
};
template <class T> array<T>::array(){
	row = 0;
	column = 0;
	A = new T*[row];
	for (int i = 0; i < row; i++)
	{
		A[i] = new T[column];
	}
}

template <class T> array<T>::array(int m, int n){
	row = m;
	column = n;
	A = new T*[row];
	for (int i = 0; i < row; i++)
	{
		A[i] = new T[column];
	}
	cout << "Initialization done" << endl;;
}

template <class T> void array<T>::set_size(int m, int n){
	row = m;
	column = n;
	A = new T*[row];
	for (int i = 0; i < row; i++)
	{
		A[i] = new T[column];
	}
//	cout << "Size set" << endl;
}

template <class T> array<T>:: ~array<T>(){
	if(row){
		for(int i = 0; i < row; i++){
			delete [] A[i];
						delete [] A;
//						cout << "deleted" << endl;
		}

	}
}
template <class T> void array<T>::read_values(){
	getData();
}
template <class T> void array<T>::display()
				{
	for (int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			cout<< A[i][j] << "\t";
		}
		cout << endl;
	}

				}

template <class T> void array<T>::getData()
				{
	cout << "Enter the value for the matrix" << endl;
	for (int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			cin>> A[i][j];
		}
	}
				}

template <class T> array<T> array<T>::operator + (array matrix2){
	array<T> temp_matrix(row,column);
	for (int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			temp_matrix.A[i][j] = A[i][j] + matrix2.A[i][j];

		}

	}
	return (temp_matrix);
}

template <class T> array<T> array<T>::operator - (array matrix2){
	array<T> temp_matrix(row,column);
	for (int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			temp_matrix.A[i][j] = A[i][j] - matrix2.A[i][j];

		}
	}
	return (temp_matrix);
}

template <class T> array<T> array<T>::operator * (array matrix2){
	array<T> temp_matrix(row,matrix2.column);
	temp_matrix.initialize();
	for (int i = 0; i < row; i++)
	{
		for(int j = 0; j < matrix2.column; j++)
		{
			for(int k = 0; k < column; k++)
			{
				temp_matrix.A[i][k] += A[i][j]*matrix2.A[j][k];
			}
		}
	}
	return (temp_matrix);
}
//template <class T> void array<T>::add(array matrix2)
//{
//	matrix1
//}

template <class T> void array<T> :: initialize(){
	for (int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			A[i][j] = 0;
		}
	}
}

template <class T> T & array<T>::operator() (int i, int j){
	return A[i][j];
}

template <class T> int array<T>::get_row_size(){
	return row;
}

template <class T> int array<T>::get_column_size(){
	return column;
}

template <class T> void array<T>::transpose(array<T> & arr){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			arr(j,i) = A[i][j];
		}
	}
}

template <class T> void array<T>::multiply(array<T> & arr1, array<T> & result){
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < arr1.get_column_size(); j++){
			result(i,j) = 0;
			for(int k = 0; k < column; k++){
				result(i,j) += A[i][k]*arr1(k,j);
			}
		}
	}
}

template <class T> void array<T>::multiply(Vector<T> & vec, Vector<T> & res){
	for(int i = 0; i < row; i++){
		int val = 0;
		for(int j = 0; j < column; j++){
			val += A[i][j]*vec[j];
		}
		res[i] = val;
	}
}
template<class T> void array<T>::zeros(){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			A[i][j] = 0;
		}
	}
}
template <class T> void array<T>::inverse_66(array<T> & result){

	double tem=0 ,temp=0,temp1=0,temp2=0,temp4=0,temp5=0;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			if(i == j){
				result(i,j) = 1.0;
			}
			else{
				result(i,j) = 0.0;
			}
		}

	}
	int i=0,j=0,p=0,q=0;
	for(i=0;i<row;i++)


	{
		temp=A[i][i];
		if(temp<0)
			temp=temp*(-1);
		p=i;
		for(j=i+1;j<row;j++)


		{
			if(A[j][i]<0)
				tem=A[j][i]*(-1);
			else
				tem=A[j][i];
			if(temp<0)
				temp=temp*(-1);
			if(tem>temp)


			{
				p=j;
				temp=A[j][i];
			}
		}
		//row exchange in both the matrix
		for(j=0;j<row;j++)


		{
			temp1=A[i][j];
			A[i][j]=A[p][j];
			A[p][j]=temp1;
			temp2=result(i,j);
			result(i,j)=result(p,j);
			result(p,j)=temp2;
		}
		//dividing the row by a[i][i]
								   temp4=A[i][i];
		for(j=0;j<row;j++)


		{
			A[i][j]=(double)A[i][j]/temp4;
			result(i,j)=(double)result(i,j)/temp4;
		}
		//making other elements 0 in order to make the matrix a[][] an indentity matrix and obtaining a inverse b[][] matrix
		for(q=0;q<row;q++)


		{
			if(q==i)
				continue;
			temp5=A[q][i];
			for(j=0;j<row;j++)


			{
				A[q][j]=A[q][j]-(temp5*A[i][j]);
				result(q,j)=result(q,j)-(temp5*result(i,j));
			}
		}
	}

}

template<class T> void array<T>::copy(array<T> & result){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			result(i,j) = A[i][j];
		}
	}
}
#endif /* ARRAY_H_ */
