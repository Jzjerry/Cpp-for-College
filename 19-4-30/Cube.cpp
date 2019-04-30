#include<iostream>

using namespace std;

class cube
{
	public:
		cube(){}
		cube(double,double,double);
		~cube(){}
		void out();
		inline void setting(double,double,double);
		inline int volume();
		inline int area();
	private:
		double height,width,length;
};

cube::cube(double x=0,double y=0,double z=0)
{
	height=x;
	width=y;
	length=z;
}

void cube::out()
{
	cout<<"H="<<height<<" W="<<width<<" L="<<length<<endl;
}

inline int cube::volume()
{
	return height*width*length;
}

inline int cube::area()
{
	return (height*width+length*height+width*length)*2;
}

inline void cube::setting(double x,double y,double z)
{
	cin>>x>>y>>z;
	length=x;
	width=y;
	height=z;
}
int main()
{
	cube A(0,0,0);
	cout<<A.volume()<<" "<<A.area()<<endl;
	A.setting(1,2,3);
	cout<<A.volume()<<" "<<A.area()<<endl;
	return 0;
}
