#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	double x=1;
	while(fabs(3*x*x*x-4*x*x-5*x+13)>1e-6)
	{
		x=x-((3*x*x*x-4*x*x-5*x+13)/(9*x*x-8*x-5));
	}
	cout<<x;
	return 0;
} 
