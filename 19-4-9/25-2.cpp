#include<iostream>

using namespace std;

void f(float x,int *y,float *z)
{
	float p=x-(int)x;
	*y=(int)x;
	*z=p;
}

int main()
{
	float a;
	int b=0;
	float c=0;
	cin>>a;
	f(a,&b,&c);
	cout<<a<<" "<<b<<" "<<c<<endl;
	return 0;
}
