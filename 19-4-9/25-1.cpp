#include<iostream>

using namespace std;

/*void invert(int* a,int n)
{
	int temp;
	for(int i=0;i<n-i-1;i++)
	{
		temp=a[i];
		a[i]=a[n-1-i];
		a[n-1-i]=temp;
	}
}*/
void invert(int* a,int n)
{
	int temp;
	for(int i=0;i<n-i-1;i++)
	{
		int* p=a+i;
		int* q=a+n-1-i;
		temp=*p;
		*p=*q;
		*q=temp;
	}
}
int main()
{
	int array[101]={0};
	int n;
	int* p;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>array[i];
	}
	invert(array,n);
	for(int i=0;i<n;i++)
	{
		cout<<array[i]<<" ";
	}
	return 0;
}
