#include<iostream>

using namespace std;

void invert(int x[],int n)
{
	int temp=0;
	for(int i=0;i<n/2;i++)
	{
		temp=x[n-1-i];
		x[n-1-i]=x[i];
		x[i]=temp;
	}
}

int main()
{
	int array[101]={0};
	int n;
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
