#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <iostream>
using namespace std;
template <class T>
class matrix
{
    T **Mat;
    int m,n;
public:
    matrix();
    matrix(int, int);
    void getmatrix();
    void displaymatrix();
    matrix operator+(const matrix&);
    matrix operator-(const matrix&);
    matrix operator*(const matrix&);
    void multi(matrix & ,matrix &);
    matrix trans();
    matrix identitymat();
    matrix zeromat();
    T & operator()(int i,int j,int k)
    {
        return Mat[i][j];
    }
    void insert_value(int i, int j, T val)
    {
        Mat[i][j]=val;
    }
    void inv2(matrix<T> & In)
    {
        T det;
        det=Mat[0][0]*Mat[1][1]-Mat[0][1]*Mat[1][0];
        In.Mat[0][0]=Mat[1][1]/det;
        In.Mat[0][1]=-1*Mat[0][1]/det;
        In.Mat[1][0]=-1*Mat[1][0]/det;
        In.Mat[1][1]=Mat[0][0]/det;
    }
    ~ matrix ()
    {
        if (m)
        {
            for (int i=0; i<m; i++)
                delete [] Mat[i];
                delete [] Mat;
        }
    }
} ;

template<class T> matrix<T>::matrix(){
	 m=0;n=0;
	  Mat = new T *[m];
	for(int i = 0; i < m; i++){
			Mat[i] = new T [n];
	}
}
template <class T>
matrix<T>::matrix(int x, int y)
    {
        m=x;n=y;
        Mat = new T *[m];
	for(int i = 0; i < m; i++){
		Mat[i] = new T [n];
    }
    }

template <class T>
void matrix<T>::getmatrix()
    {
        cout<<"enter matrix elements of size"<<m<<"*"<<n<<":";
        for (int i=0;i<m;i++)
            for (int j=0;j<n;j++)
            cin>>Mat[i][j];
    }
template <class T>
void matrix<T>::displaymatrix()
    {
        for (int i=0;i<m;i++)
        {
            cout<<endl;
            for (int j=0;j<n;j++)
                cout<<Mat[i][j]<<"  ";
        }
    }
template <class T>
matrix<T> matrix<T>::operator+(const matrix& M)
    {
        matrix N(m,n);
        for (int i=0;i<m;i++)
            for (int j=0;j<n;j++)
                N.Mat[i][j]=this->Mat[i][j]+M.Mat[i][j];
            return N;
    }
template <class T>
matrix<T>  matrix<T>::operator-(const matrix& M)
    {
        matrix N(m,n);
        for (int i=0;i<m;i++)
            for (int j=0;j<n;j++)
                N.Mat[i][j]=this->Mat[i][j]-M.Mat[i][j];
            return N;
    }
template <class T>
matrix<T> matrix<T>::operator*(const matrix& M)
    {
        matrix N(m,M.n);
        for (int i=0;i<m;i++)
            for (int j=0;j<M.n;j++)
            {
              N.Mat[i][j]=0;
              for (int k=0;k<n;k++)
                    N.Mat[i][j]+=Mat[i][k]*M.Mat[k][j];
            }
            return N;
    }
template <class T>
void matrix<T>::multi(matrix<T> &M ,matrix<T> &N)
    {
        //matrix N(m,M.n);
        for (int i=0;i<m;i++)
            for (int j=0;j<M.n;j++)
            {
              N.Mat[i][j]=0;
              for (int k=0;k<n;k++)
                    N.Mat[i][j]+=Mat[i][k]*M.Mat[k][j];
            }
          //  return N;
    }
template <class T>
 matrix<T> matrix<T>::trans()
    {
        matrix N(n,m);
        for (int i=0;i<m;i++)
            for (int j=0;j<n;j++)
                N.Mat[j][i]=Mat[i][j];
            return N;
    }
template <class T>
 matrix<T> matrix<T>::identitymat()
    {
        matrix N(n,m);
        for (int i=0;i<m;i++)
            for (int j=0;j<n;j++){
                if (i==j)
                N.Mat[i][j]=1;
                else
                    N.Mat[i][j]=0;
            }
            return N;
    }
template <class T>
 matrix<T> matrix<T>::zeromat()
    {
        matrix N(n,m);
        for (int i=0;i<m;i++)
            for (int j=0;j<n;j++)
                    N.Mat[i][j]=0;
            return N;
    }
#endif // MATRIX_H_INCLUDED
