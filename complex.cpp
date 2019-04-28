//�������ǶԸ�������дʵ��// 
//ּ����ϰ �ṹ�塢�������������������// 

#include<iostream>

using namespace std;

struct complex										//���������ṹ�� 
{
	//������ʵ���鲿���ɣ���������double�ֱ�������� 
	double re,im;
	complex(){}										//���캯�� 
	complex(double re,double im):re(re),im(im){}	//���ع��캯�� 
	inline void real(const double& x){re=x;}		//��ʵ�������޸� 
	inline void imag(const double& y){im=y;}		//���鲿�����޸� 
	inline double real(){return re;}				//����real����������ֵΪʵ�� 
	inline double imag(){return im;}				//����imag����������ֵΪ�鲿 
	inline void output(){cout<<re<<"+"<<im<<"i"<<endl;}	//�����������n+mi����ʽ������� 
	inline complex operator + (const complex& rhs)		//�����������㣬������ϸ������� 
	const{return complex(re+rhs.re,im+rhs.im);}
	inline complex operator -(const complex& rhs) 
	const{return complex(re-rhs.re,im+rhs.im);}
	inline complex operator *(const complex& rhs)
	const{return complex(re*rhs.re-im*rhs.im,re*rhs.re+im*rhs.im);}
	inline void operator /=(const double& n)			//Ҫע������ֻ��������ʵ������ 
	{re/=n,im/=n;}
	inline void operator *=(const complex& rhs)
	{*this=complex(re*rhs.re-im*rhs.im,re*rhs.im+im*rhs.re);}
	inline void operator +=(const complex& rhs)
	{re+=rhs.re,im+=rhs.im;}
	inline complex conj()								//ȡ��������� 
	{
		return complex(re,-im);
	}
};

//typedef struct complex jint;							//�˴���һ�����Ͷ����ʹ����� 

//Example on using struct & pointer of struct
int main()
{
	complex a(1,2);
	cout<<a.re<<" "<<a.im<<endl;						//��һ���������a��ʵ�����鲿 
	a.output();											//���ó�Ա������1+2i����ʽ��� 
	double complex::*p=&complex::re;					//ָ���Ա������ָ��ı�׼���� 
	complex b,*opt=&b;									//optΪָ�����ṹ��b��ָ�� 
	double(complex::*pfun)()=&complex::imag;			//ָ���Ա������ָ��ı�׼���� 
	b.*p=2.0;											//��ָ����ʵ�ֶ�b��ʵ�������޸� 
	p=&complex::im;										//�ı�ָ��p��ָ������ָ���鲿 
	opt->*p=400;										//ͨ���ṹ��ָ��opt��ָ��p����޸� 
	b.output();											//���ó�Ա������� 
	cout<<(b.*pfun)()<<endl;							//ʹ�ó�Ա����ָ������鲿 
	return 0;
}
