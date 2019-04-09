#include<algorithm>
#include<iostream>

using namespace std;

int comp(int a,int b)
{
	return a>b?a:b;
}

int maxn(int a[],int n)
{
	int temp=0;
	for(int i=0;i<n;i++)
	{
		temp=comp(temp,a[i]);
	}
	return temp;
}

int main()
{
	int array[101]={0};
	int t;
	int max;
	cin>>t;
	for(int i=0;i<t;i++)
	{
		cin>>array[i];
	}
	cout<<maxn(array,t)<<endl;
	return 0;
}
