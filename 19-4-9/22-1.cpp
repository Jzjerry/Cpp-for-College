#include<iostream>

using namespace std;

int lookup(int x[],int n,int y)
{
	for(int i=0;i<n;i++)
	{
		if(x[i]==y)
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	int array[101]={0};
	int find;
	int n;
	cin>>n;
	cin>>find;
	for(int i=0;i<n;i++)
	{
		cin>>array[i];
	}
	cout<<lookup(array,n,find)<<endl;
	return 0;
}
