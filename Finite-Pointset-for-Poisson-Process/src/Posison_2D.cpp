//============================================================================
// Name        : Posison_2D.cpp
// Author      : saurabh
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Domain.h"
#include "array.h"
#include "IterativeSolver.h"
using namespace std;


int main() {
	Domain dmn;

	dmn.initialize();
//
	dmn.fill_domain();
//	cout << "Reached Main" << endl;
//	cout << "Reached Line 21" << endl;
	dmn.write();
	dmn.createMatrix();
//	Point point;
//	point.set_global_index(2);

//	Vector<double> vec;
//	vec.set_size(5);
//	vec.read_values();
//	vec.display();
//	vec[3] = vec[4];
//	vec.display();

//	array<double> arr;
//	arr.set_size(6,6);
//	arr.read_values();
//	arr.display();
//	array<double> res;
//	res.set_size(6,6);
//	arr.inverse_66(res);
//	res.display();
//	cout << "******************" << endl;
//	arr.display();
//	float a[10][10],b[10][10],tem=0,temp=0,temp1=0,temp2=0,temp4=0,temp5=0;
//	    	int n=0,m=0,i=0,j=0,p=0,q=0;
//	    	cout << "Enter size of 2d array(Square matrix) :";
//	    	cin >> n;
//	    	for(i=0;i<n;i++)
//
//
//	        	{
//	        		for(j=0;j<n;j++)
//
//
//	            		{
//	        			cout << "Enter the element number " << i << j ;
//
////	            			printf("Enter element no. %d %d :",i,j);
//	        			cin >> a[i][j];
////	            			scanf("%f",&a[i][j]);
//	            			if(i==j)
//	            			b[i][j]=1;
//	            			else
//	            			b[i][j]=0;
//	            		}
//	            	}
//	            	for(i=0;i<n;i++)
//
//
//	                	{
//	                		temp=a[i][i];
//	                		if(temp<0)
//	                		temp=temp*(-1);
//	                		p=i;
//	                		for(j=i+1;j<n;j++)
//
//
//	                    		{
//	                    			if(a[j][i]<0)
//	                    				tem=a[j][i]*(-1);
//	                    			else
//	                    				tem=a[j][i];
//	                    			if(temp<0)
//	                    				temp=temp*(-1);
//	                    			if(tem>temp)
//
//
//	                        			{
//	                        				p=j;
//	                        				temp=a[j][i];
//	                        			}
//	                        		}
//	                        		//row exchange in both the matrix
//	                        		for(j=0;j<n;j++)
//
//
//	                            		{
//	                            			temp1=a[i][j];
//	                            			a[i][j]=a[p][j];
//	                            			a[p][j]=temp1;
//	                            			temp2=b[i][j];
//	                            			b[i][j]=b[p][j];
//	                            			b[p][j]=temp2;
//	                            		}
//	                            		//dividing the row by a[i][i]
//	                            		temp4=a[i][i];
//	                            		for(j=0;j<n;j++)
//
//
//	                                		{
//	                                			a[i][j]=(float)a[i][j]/temp4;
//	                                			b[i][j]=(float)b[i][j]/temp4;
//	                                		}
//	                                		//making other elements 0 in order to make the matrix a[][] an indentity matrix and obtaining a inverse b[][] matrix
//	                                		for(q=0;q<n;q++)
//
//
//	                                    		{
//	                                    			if(q==i)
//	                                    				continue;
//	                                    			temp5=a[q][i];
//	                                    			for(j=0;j<n;j++)
//
//
//	                                        			{
//	                                        				a[q][j]=a[q][j]-(temp5*a[i][j]);
//	                                        				b[q][j]=b[q][j]-(temp5*b[i][j]);
//	                                        			}
//	                                        		}
//	                                        	}
//	                                        	for(i=0;i<n;i++)
//
//
//	                                            	{
//	                                            		for(j=0;j<n;j++)
//
//
//	                                                		{
//	                                                			printf("%.3f	",b[i][j]);
//	                                                		}
//	                                                		printf("\n");
//	                                                	}
//	                                                	return 0;
//	                                            }
//


}


