#include<iostream>

using namespace std;

bool is_circle(int a)
{
	if(a<10)
	{
		return true;
	}
	else if(a<100)
	{
		if(a%10==a/10)
		{
			return true;
		}
		else return false;
	}
	else if(a<1000)
	{
		if(a%10==a/100)
		{
			return true;
		}
		else return false;
	}
	else return false;
}


int main()
{
	for(int i=1;i<=500;i++)
	{
		if(is_circle(i))
		{
			cout<<i<<endl;
		}
	}
	return 0;
}
