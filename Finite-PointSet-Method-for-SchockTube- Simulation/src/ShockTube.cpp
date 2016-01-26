#include<iostream>
using namespace std;
#include"point1dnew.h"
int main()
{
    shock<double> s;


    s.get_data();
    s.fill_points();
    s.display_points();
    for (int i=0;i<200;i++)
    {
    s.simulate();
    //cout<<i<<endl;
    }
    s.display_points();
    s.write_file();
    return 0;
}
