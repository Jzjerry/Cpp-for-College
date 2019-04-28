//本程序是对复数的手写实现// 
//旨在练习 结构体、内联函数、运算符重载// 

#include<iostream>

using namespace std;

struct complex										//声明复数结构体 
{
	//复数由实部虚部构成，声明两个double分别代表他们 
	double re,im;
	complex(){}										//构造函数 
	complex(double re,double im):re(re),im(im){}	//重载构造函数 
	inline void real(const double& x){re=x;}		//对实部进行修改 
	inline void imag(const double& y){im=y;}		//对虚部进行修改 
	inline double real(){return re;}				//重载real函数，返回值为实部 
	inline double imag(){return im;}				//重载imag函数，返回值为虚部 
	inline void output(){cout<<re<<"+"<<im<<"i"<<endl;}	//输出函数，以n+mi的形式输出虚数 
	inline complex operator + (const complex& rhs)		//重载四则运算，让其符合复数运算 
	const{return complex(re+rhs.re,im+rhs.im);}
	inline complex operator -(const complex& rhs) 
	const{return complex(re-rhs.re,im+rhs.im);}
	inline complex operator *(const complex& rhs)
	const{return complex(re*rhs.re-im*rhs.im,re*rhs.re+im*rhs.im);}
	inline void operator /=(const double& n)			//要注意这里只是重载了实数除法 
	{re/=n,im/=n;}
	inline void operator *=(const complex& rhs)
	{*this=complex(re*rhs.re-im*rhs.im,re*rhs.im+im*rhs.re);}
	inline void operator +=(const complex& rhs)
	{re+=rhs.re,im+=rhs.im;}
	inline complex conj()								//取共轭复数函数 
	{
		return complex(re,-im);
	}
};

//typedef struct complex jint;							//此处是一个类型定义的使用语句 

//Example on using struct & pointer of struct
int main()
{
	complex a(1,2);
	cout<<a.re<<" "<<a.im<<endl;						//第一次输出的是a的实部与虚部 
	a.output();											//调用成员函数以1+2i的形式输出 
	double complex::*p=&complex::re;					//指向成员变量的指针的标准声明 
	complex b,*opt=&b;									//opt为指向复数结构体b的指针 
	double(complex::*pfun)()=&complex::imag;			//指向成员函数的指针的标准声明 
	b.*p=2.0;											//从指针上实现对b的实部进行修改 
	p=&complex::im;										//改变指针p的指向，现在指向虚部 
	opt->*p=400;										//通过结构体指针opt与指针p完成修改 
	b.output();											//调用成员函数输出 
	cout<<(b.*pfun)()<<endl;							//使用成员函数指针输出虚部 
	return 0;
}
