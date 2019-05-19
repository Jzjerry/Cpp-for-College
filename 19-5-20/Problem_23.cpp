#include<iostream>
#include<cmath>

using namespace std;

int f(char *c,int length)
{
	int i=0;
	int count=0;
	for(i=0;i<length;i++)
	{
		if(c[i]>='0'&&c[i]<='9')
		{
			count++;
		}
	}
	return count;
}

int main()
{
	char s[100];
	int j;
	for(j=0;j<=99;j++)
	{
		s[j]=234*cos(j*0.6);
	}
	cout<<f(s,100)<<endl;
	return 0;
}
