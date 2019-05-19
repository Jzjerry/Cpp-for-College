#include<iostream>

using namespace std;

int f(int M,int N)
{
	int i,j;
	int count=0;
	if(M<=0||N<=0){return -1;}
	else
	{ 
		for(i=2;i<=N;i+=2)
		{
			for(j=1;j<=N;j+=2)
			{
				if(7*i+4*j==M)
				{
					count++;
				}
			}
		}
		return count;
	}
} 
int main(int argc,char *argv[])
{
	int m,n;
	cin>>m>>n;
	cout<<f(m,n)<<endl;
	return 0;
}
