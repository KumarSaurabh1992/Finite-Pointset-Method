#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include<cmath>
#include <iostream>
using namespace std;
template<class T>
class vect
{
    int SIZE,Size,inc;
    T *v;
public:
    vect();
    vect(int);
void  get_vect();
void display_vect();
 T  & vect_out(int);
 T innrpro(vect &);
 vect operator+(vect&);
 vect operator-(vect& );
 void  operator()(int);
 void  add(vect&);
 void  subtract(vect&);
 vect<T> operator*(T);
 void add3vect(vect&,T,vect&,T,vect&);
 void add2vect(vect&,T,vect&);
void operator=(vect &v1)
{
    SIZE=v1.SIZE;
    Size=v1.Size;
    for (int i=0;i<SIZE;i++)
    v[i]=v1.v[i];
}
 T & operator[](int);
 T dist2(vect&);
 void Resize(int);
 void get_inc(int i){inc=i;}
 int & current_size( ){ return Size;}
 int length()
 {
     return SIZE;
 }
 //T vect_dot(vect);
 friend istream &operator>>( istream  &input, vect &D )
 {     for (int i=0;i<D.SIZE;i++)
     input>>D.v[i];
     return input;
 }
 friend ostream &operator<<( ostream  &output, vect &D )
  {     for (int i=0;i<D.SIZE;i++)
         output<<D.v[i]<<" ";
         output<<endl;
     return output;
 }
void vect_del()
{
    if(SIZE)
    {
    delete v;
    SIZE=0;
    }
}
~ vect()
{
    if (SIZE)
    delete v;
}
};

template<class T> vect<T>::vect(){
	SIZE=0;Size=0;inc=0;
	v=new T [SIZE];
}
template <class T>
vect<T>::vect(int x)
{
    SIZE=x;Size=0;inc=0;
    v=new T [SIZE];
}
template <class T>
void vect<T>::get_vect()
{
    cout<<"Enter vector elements:";
    //for(int i=0;i<SIZE;i++)
    cin>>*this;
}
template <class T>
void vect<T>::display_vect()
{
cout<<"Vector elements are:\n";
for(int i=0;i<SIZE;i++)
    cout<<v[i]<<" ";
cout<<endl;
}
template <class T>
T & vect<T>::vect_out(int i)
{
    return (v[i]);
}
template <class T>
vect<T> vect<T>::operator+(vect<T> &v1)
{
    vect<T> v_sum(SIZE);
    for(int i=0;i<SIZE;i++)
    v_sum.v[i]=v[i]+v1.v[i];
    return v_sum;
}
template <class T>
vect<T> vect<T>::operator-(vect<T> &v1)
{
    vect<T> v_sum(SIZE);
    for(int i=0;i<SIZE;i++)
    v_sum.v[i]=v[i]-v1.v[i];
    return v_sum;
}

template <class T>
void  vect<T>::operator()(int M)
{
    SIZE=M;inc=0;Size=0;
    v=new T [SIZE];
}
template <class T>
T & vect<T>::operator[](int i)
{
    //if(i<SIZE)
    return v[i];
    //else
    //return T();
}
template <class T>
void vect<T>::Resize(int min_siz)
{

    int nsize=(inc)?SIZE+inc:2*SIZE;
    if(nsize<min_siz)
        nsize=min_siz;
       // cout<<endl<<nsize<<endl;
    int n=(SIZE<nsize)?SIZE:nsize;
    T *temp_vect;
    //cout<<"dfdfd="<<nsize;
    temp_vect=new T [nsize];
    //cout<<"...........";
     memcpy(temp_vect,v,nsize*sizeof(T));
    delete v;
    //cout<<"jbfjjkf"<<temp_vect;

    v=temp_vect;
    Size=SIZE=nsize;
    inc=0;
   // cout<<inc<<endl;

}
template <class T>
T vect<T>::dist2(vect<T> &v1)
{
    T d2=(v[0]-v1.v[0])*(v[0]-v1.v[0]);
    for ( int i=1;i<SIZE;i++)
        d2+=(v[i]-v1.v[i])*(v[i]-v1.v[i]);
    return sqrt(d2);
}
template <class T>
T vect<T>::innrpro(vect<T> &x)
{
    T d=v[0]*x.v[0];
    for(int i=1;i<SIZE;i++)
    {
        d+=v[i]*x.v[i];
    }
    return d;
}
template <class T>
vect<T> vect<T>::operator*(T  a)
{
    vect<T> v1(SIZE);
    for(int i=0;i<SIZE;i++)
    v1[i]=v[i]*a;
    return v1;
}
template <class T>
void vect<T>::add(vect<T> &a)
{
    for(int i=0;i<SIZE;i++)
        v[i]+=a[i];
}
template <class T>
void vect<T>::subtract(vect<T> &a)
{
    for(int i=0;i<SIZE;i++)
        v[i]-=a[i];
}
template <class T>
void vect<T>::add3vect(vect<T> &v1,T a,vect<T> &v2,T b,vect<T> &v3)
{
    for (int i=0;i<SIZE;i++)
        v[i]=v1[i]+a*v2[i]+b*v3[i];
}
template <class T>
void vect<T>::add2vect(vect<T> &v1,T a,vect<T> &v2)
{
    for (int i=0;i<SIZE;i++)
        v[i]=v1[i]+a*v2[i];

}


#endif // VECTOR_H_INCLUDED
