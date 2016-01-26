#ifndef POINT1D_H_INCLUDED
#define POINT1D_H_INCLUDED
#include "vector.h"
#include "matrix.h"
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<ctime>
template <class T>
class point{

	T x;
	T rho,v,pr,e;
	int boundary;
	vect<int> nbd;
public:
	point();
	point (T);
	T & get_point()
	{
		return x;
	}
	T & density(){return rho;}
	T & velocity(){return v;}
	T & pressure(){return pr;}
	T & energy(){return e;}
	void set_nbd(int);
	void neighbour(int);
	void display_nbd();
	void nbd_zero();
	int nbd_size();
	int nbd_element(int);
};
template <class T> point<T>::point(){
	x = 0;
	boundary = 0;
	nbd(0);
}
template <class T> point<T>::point(T val){
	x = val;
	boundary = 0;
	nbd = new int[0];
}

template <class T>
void point<T>::set_nbd(int M)
{
	nbd(M);
}
template <class T>
void point<T>::neighbour(int j)
{
	int counter;
	counter=nbd.current_size();
	nbd[counter]=j;
	nbd.current_size()++;
}
template <class T>
void point<T>::nbd_zero()
{
	nbd.current_size()=0;
}
template <class T>
void point<T>::display_nbd()
{

	int i,n;
	n=nbd.current_size();
	for(i=0;i<n;i++)
		cout<<nbd[i]<<" ";
}
template <class T>
int point<T>::nbd_size()
{
	return nbd.current_size();
}
template <class T>
int point<T>::nbd_element(int i)
{
	return nbd[i];
}
template <class T>
class shock{
	T alpha,beta,h,gamma,kapa,mu,dt,Rg;
	int N,M,L,R;
	point<T> *p, *newp;
	//vect<int> *Box;
public:
	void   get_data();
	void fill_points();
	void set_neighbour(int);
	void set_neighbour_newp(int);
	void display_points();
	void simulate();
	void Fpm_velocit_p(int,T&,T&);
	void Fpm_pressure_p(int,T&);
	void Fpm_energy_p(int,T&);
	void Fpm_velocit_newp(int,T&,T&);
	void Fpm_pressure_newp(int,T&);
	void Fpm_energy_newp(int,T&);
	void write_file();
	void test();
};
template <class T>
void shock<T>::get_data()
{
	cout<<"\nEnter  h:";
	cin>>h;
	alpha=0.4;beta=0.5;
	gamma=1.41;
	mu=0.0005;
	kapa=0.0005;
	dt=0.001;
	Rg=8.314;
	N=(int)ceil(1/(alpha*h));
	M=(int)floor(1/h);
	L=(int)floor(1/alpha);

	p=new point<T> [N];
	newp=new point<T> [N];

}
template <class T>
void shock<T>::fill_points()
{
	int i,k;
	T r,val;

	srand (time(NULL));
	for (i=0;i<N;i++)
	{
		newp[i].set_nbd(2*L);
		p[i].set_nbd(2*L);
	}
	p[0].get_point()=0;
	p[0].density()=1;
	p[0].velocity()=0;
	p[0].energy()=2.5;
	p[0].pressure()=(gamma-1)*p[0].density()*p[0].energy();
	//p[0].set_nbd(L);
	k=0;i=0;
	while(k==0)
	{
		i++;
		r=alpha*h+((T)rand()/(RAND_MAX))*(beta-alpha)*h;
		val=p[i-1].get_point()+r;
		if (fabs(1-val)<beta*h)
		{
			if (fabs(0.5-val)<alpha*h)
				val=val-((T)rand()/(RAND_MAX))*(beta-2*alpha)*h;
			else{

				k=1;
			}
		}
		if (val<0.5)
		{
			p[i].get_point()=val;
			p[i].density()=1;
			p[i].velocity()=0;
			p[i].energy()=2.5;
			p[i].pressure()=(gamma-1)*p[i].density()*p[i].energy();
			//p[i].set_nbd(2*L);
			set_neighbour(i);
		}
		else
		{
			p[i].get_point()=val;
			p[i].density()=0.125;
			p[i].velocity()=0;
			p[i].energy()=2.0;
			p[i].pressure()=(gamma-1)*p[i].density()*p[i].energy();
			//p[i].set_nbd(2*L);
			set_neighbour(i);

		}
	}

	i++;
	val=1;
	p[i].get_point()=val;
	p[i].density()=0.125;
	p[i].velocity()=0;
	p[i].energy()=2.0;
	p[i].pressure()=(gamma-1)*p[i].density()*p[i].energy();
	//p[i].set_nbd(L);
	set_neighbour(i);

	R=i+1;
}

template <class T>
void shock<T>::set_neighbour(int i)
{
	int n,k;
	T pval,pval1;
	pval=p[i].get_point();
	k=0;
	n=i-1;
	while(k==0 && n >=0)
	{
		pval1=p[n].get_point();
		if (fabs(pval-pval1)<=h)
		{
			p[i].neighbour(n);
			p[n].neighbour(i);
			n--;
		}
		else
			n--;
	}
}

template <class T>
void shock<T>::set_neighbour_newp(int i)
{
	int n,k;
	T pval,pval1;
	pval=newp[i].get_point();
	k=0;
	n=i-1;

	while(k==0 && n >=0)
	{

		pval1=newp[n].get_point();
		if (fabs(pval-pval1)<=h)
		{
			//cout<<"\n..->"<<n<<".."<<pval-pval1;
			newp[i].neighbour(n);
			newp[n].neighbour(i);
			n--;
		}
		else
			n--;
	}

	//cout<<"\n..->"<<n;
}

template <class T>
void shock<T>::display_points()
{
	int m;
	for(int i=0;i<R;i++)
	{
		cout<<i<<"->"<<p[i].get_point()<<" nbd  :";
		m=p[i].nbd_size();
		for(int l=0;l<m;l++)
			cout<<p[i].nbd_element(l)<<" ";
		//p[i].display_nbd();
		cout<<endl;
	}
}
template <class T>
void shock<T>::simulate()
{
	int i;
	T vd,vdd,pd,edd;
	for (i=0;i<R;i++)
		newp[i].nbd_zero();

	//cout<<R<<endl;
	for(i=0;i<R;i++)
	{
		Fpm_velocit_p(i,vd,vdd);
		Fpm_pressure_p(i,pd);
		Fpm_energy_p(i,edd);
		//cout<<i<<"-> "<<vd<<" "<<vdd<<" "<<pd<<" "<<edd<<endl;
		newp[i].density()=p[i].density()*(1-(dt/2)*vd);
		newp[i].velocity()=p[i].velocity()+(dt/2)*(1/(p[i].density()))*((4.0/3)*mu*vdd-pd);
		newp[i].energy()=p[i].energy()+(dt/2)*(1/(p[i].density()))*((4.0/3)*mu*vd*vd-p[i].pressure()*vd+kapa*((gamma-1)/Rg)*edd);
		newp[i].pressure()=(gamma-1)*newp[i].density()*newp[i].energy();
		newp[i].get_point()=p[i].get_point()+(dt/2)*newp[i].velocity();

		set_neighbour_newp(i);


		//     newp[i].density()=p[i].density()-(dt/2)*p[i].density()*(vd);
		//     newp[i].velocity()=p[i].velocity()+(dt/(2*p[i].density()))*(-1*pd+(4/3)*mu*vdd);
		//     newp[i].energy()=p[i].energy()+(dt/(2*p[i].density()))*(-1*p[i].pressure()*vd+(4/3)*mu*(vd*vd)+kapa*((gamma-1)/Rg)*edd);
		//     newp[i].pressure()=(gamma-1)*newp[i].density()*newp[i].energy();
		//     newp[i].get_point()=p[i].get_point()+(dt/2)*newp[i].velocity();
		//     set_neighbour_newp(i);
	}

	// for (i=0;i<R;i++)
	//    p[i].nbd_zero();

	for(i=0;i<R;i++)
	{
		Fpm_velocit_newp(i,vd,vdd);
		Fpm_pressure_newp(i,pd);
		Fpm_energy_newp(i,edd);
		// cout<<i<<"-> "<<vd<<" "<<vdd<<" "<<pd<<" "<<edd<<endl;


		p[i].density()=p[i].density()-dt*newp[i].density()*vd;
		p[i].velocity()=p[i].velocity()+dt*(1/(newp[i].density()))*((4.0/3)*mu*vdd-pd);
		p[i].energy()=p[i].energy()+dt*(1/(newp[i].density()))*((4.0/3)*mu*vd*vd-newp[i].pressure()*vd+kapa*((gamma-1)/Rg)*edd);
		p[i].pressure()=(gamma-1)*p[i].density()*p[i].energy();
	}
}

template <class T>
void shock<T>::Fpm_velocit_p(int i,T& vd,T& vdd)
{
	int m,j,k,l;
	m=p[i].nbd_size();
	T pval,pval1,dx,dx2,w,u,u1;
	matrix<T> Ma(m,2),MaT(2,m),W(m,m),b(m,1),U(2,1);
	pval=p[i].get_point();
	u=p[i].velocity();
	for (j=0;j<m;j++)
	{
		k=p[i].nbd_element(j);
		pval1=p[k].get_point();
		u1=p[k].velocity();
		u1=u1-u;
		dx=pval1-pval;
		dx2=dx*dx/2;
		w=exp(-6.25*dx*dx/(h*h));
		Ma(j,0,0)=dx;
		Ma(j,1,0)=dx2;
		MaT(0,j,0)=dx;
		MaT(1,j,0)=dx2;
		for (l=0;l<m;l++)
			W(j,l,0)=0;
		W(j,j,0)=w;
		b(j,0,0)=u1;
	}
	matrix<T> MtW(2,m),C(2,2),Ci(2,2),D(2,m);
	MaT.multi(W,MtW);
	MtW.multi(Ma,C);
	C.inv2(Ci);
	Ci.multi(MtW,D);
	D.multi(b,U);
	vd=U(0,0,0);
	vdd=U(1,0,0);
}
template <class T>
void shock<T>::Fpm_pressure_p(int i,T& pd)
{
	int m,j,k,l;
	m=p[i].nbd_size();
	T pval,pval1,dx,dx2,w,u,u1;
	matrix<T> Ma(m,2),MaT(2,m),W(m,m),b(m,1),U(2,1);
	pval=p[i].get_point();
	u=p[i].pressure();
	for (j=0;j<m;j++)
	{
		k=p[i].nbd_element(j);
		pval1=p[k].get_point();
		u1=p[k].pressure();
		u1=u1-u;
		dx=pval1-pval;
		dx2=dx*dx/2;
		w=exp(-6.25*dx*dx/(h*h));
		Ma(j,0,0)=dx;
		Ma(j,1,0)=dx2;
		MaT(0,j,0)=dx;
		MaT(1,j,0)=dx2;
		for (l=0;l<m;l++)
			W(j,l,0)=0;
		W(j,j,0)=w;
		b(j,0,0)=u1;
	}
	matrix<T> MtW(2,m),C(2,2),Ci(2,2),D(2,m);
	MaT.multi(W,MtW);
	MtW.multi(Ma,C);
	C.inv2(Ci);
	Ci.multi(MtW,D);
	D.multi(b,U);
	pd=U(0,0,0);
}
template <class T>
void shock<T>::Fpm_energy_p(int i,T& edd)
{
	int m,j,k,l;
	m=p[i].nbd_size();
	T pval,pval1,dx,dx2,w,u,u1;
	matrix<T> Ma(m,2),MaT(2,m),W(m,m),b(m,1),U(2,1);
	pval=p[i].get_point();
	u=p[i].energy();
	for (j=0;j<m;j++)
	{
		k=p[i].nbd_element(j);
		pval1=p[k].get_point();
		u1=p[k].energy();
		u1=u1-u;
		dx=pval1-pval;
		dx2=dx*dx/2;
		w=exp(-6.25*dx*dx/(h*h));
		Ma(j,0,0)=dx;
		Ma(j,1,0)=dx2;
		MaT(0,j,0)=dx;
		MaT(1,j,0)=dx2;
		for (l=0;l<m;l++)
			W(j,l,0)=0;
		W(j,j,0)=w;
		b(j,0,0)=u1;
	}
	matrix<T> MtW(2,m),C(2,2),Ci(2,2),D(2,m);
	MaT.multi(W,MtW);
	MtW.multi(Ma,C);
	C.inv2(Ci);
	Ci.multi(MtW,D);
	D.multi(b,U);

	edd=U(1,0,0);

}

template <class T>
void shock<T>::Fpm_velocit_newp(int i,T& vd,T& vdd)
{
	int m,j,k,l;
	m=newp[i].nbd_size();
	T pval,pval1,dx,dx2,w,u,u1;
	matrix<T> Ma(m,2),MaT(2,m),W(m,m),b(m,1),U(2,1);
	pval=newp[i].get_point();
	u=newp[i].velocity();
	for (j=0;j<m;j++)
	{
		k=newp[i].nbd_element(j);
		pval1=newp[k].get_point();
		u1=newp[k].velocity();
		u1=u1-u;
		dx=pval1-pval;
		dx2=dx*dx/2;
		w=exp(-6.25*dx*dx/(h*h));
		Ma(j,0,0)=dx;
		Ma(j,1,0)=dx2;
		MaT(0,j,0)=dx;
		MaT(1,j,0)=dx2;
		for (l=0;l<m;l++)
			W(j,l,0)=0;
		W(j,j,0)=w;
		b(j,0,0)=u1;
	}
	matrix<T> MtW(2,m),C(2,2),Ci(2,2),D(2,m);
	MaT.multi(W,MtW);
	MtW.multi(Ma,C);
	C.inv2(Ci);
	Ci.multi(MtW,D);
	D.multi(b,U);
	vd=U(0,0,0);
	vdd=U(1,0,0);

}
template <class T>
void shock<T>::Fpm_pressure_newp(int i,T& pd)
{
	int m,j,k,l;
	m=newp[i].nbd_size();
	T pval,pval1,dx,dx2,w,u,u1;
	matrix<T> Ma(m,2),MaT(2,m),W(m,m),b(m,1),U(2,1);
	pval=newp[i].get_point();
	u=newp[i].pressure();
	for (j=0;j<m;j++)
	{
		k=newp[i].nbd_element(j);
		pval1=newp[k].get_point();
		u1=newp[k].pressure();
		u1=u1-u;
		dx=pval1-pval;
		dx2=dx*dx/2;
		w=exp(-6.25*dx*dx/(h*h));
		Ma(j,0,0)=dx;
		Ma(j,1,0)=dx2;
		MaT(0,j,0)=dx;
		MaT(1,j,0)=dx2;
		for (l=0;l<m;l++)
			W(j,l,0)=0;
		W(j,j,0)=w;
		b(j,0,0)=u1;
	}
	matrix<T> MtW(2,m),C(2,2),Ci(2,2),D(2,m);
	MaT.multi(W,MtW);
	MtW.multi(Ma,C);
	C.inv2(Ci);
	Ci.multi(MtW,D);
	D.multi(b,U);
	pd=U(0,0,0);

}
template <class T>
void shock<T>::Fpm_energy_newp(int i,T& edd)
{
	int m,j,k,l;
	m=newp[i].nbd_size();
	T pval,pval1,dx,dx2,w,u,u1;
	matrix<T> Ma(m,2),MaT(2,m),W(m,m),b(m,1),U(2,1);
	pval=newp[i].get_point();
	u=newp[i].energy();
	for (j=0;j<m;j++)
	{
		k=newp[i].nbd_element(j);
		pval1=newp[k].get_point();
		u1=newp[k].energy();
		u1=u1-u;
		dx=pval1-pval;
		dx2=dx*dx/2;
		w=exp(-6.25*dx*dx/(h*h));
		Ma(j,0,0)=dx;
		Ma(j,1,0)=dx2;
		MaT(0,j,0)=dx;
		MaT(1,j,0)=dx2;
		for (l=0;l<m;l++)
			W(j,l,0)=0;
		W(j,j,0)=w;
		b(j,0,0)=u1;
	}
	matrix<T> MtW(2,m),C(2,2),Ci(2,2),D(2,m);
	MaT.multi(W,MtW);
	MtW.multi(Ma,C);
	C.inv2(Ci);
	Ci.multi(MtW,D);
	D.multi(b,U);

	edd=U(1,0,0);
}
template <class T>
void shock<T>::write_file()
{
	ofstream myfile;

	myfile.open("shock.txt");
	for (int i=0;i<R;i++)
	{
		//cout<<i;
		myfile<<p[i].get_point()<<" "<<p[i].density()<<" "<<p[i].pressure()<<" "<<p[i].velocity()<<" "<<p[i].energy()<<endl;
	}
	myfile.close();
}
template <class T>
void shock<T>::test()
{
	int m,j,k,l;
	cout<<"m=";
	cin>>m;
	T a11, a12 , a22, d1,d2,pval,pval1,dx,dx2,w,u,u1,det;
	matrix<T> Ma(m,2),MaT(2,m),W(m,m),b(m,1),U(2,1);

	Ma.getmatrix();
	MaT.getmatrix();
	W.getmatrix();
	b.getmatrix();

	matrix<T> MtW(2,m),C(2,2),Ci(2,2),D(2,m);
	MaT.multi(W,MtW);
	cout<<"M'W\n";
	MtW.displaymatrix();

	MtW.multi(Ma,C);
	cout<<"M'WM\n";
	C.displaymatrix();

	C.inv2(Ci);
	cout<<"inv\n";
	Ci.displaymatrix();

	cout<<"...\n";

	Ci.multi(MtW,D);
	D.multi(b,U);
	D.displaymatrix();
	U.displaymatrix();
}
#endif // POINT1D_H_INCLUDED
