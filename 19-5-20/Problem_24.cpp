#include<iostream>

using namespace std;

void f(char *s)
{
	int i,j,count,max;
	int begin_m,begin;
	bool word_a=0;
	count=0;
	max=0;
	begin_m=0;
	begin=0;
	for(i=0;;i++)
	{
		if(s[i]!=' '&&s[i]!='\0')
		{
			count++;
			if(s[i]=='a'||s[i]=='A')
			{
				word_a=1;
			}
		}
		else
		{
			if((max<count)&&word_a)
			{
				max=count;
				begin_m=begin;
			}
			word_a=0;
			count=0;
			begin=i+1;
			if(s[i]=='\0')
			{
				break;
			}
		}
	}
	if(max==0)
	{
		cout<<"No word with a"<<endl;
		return;
	}
	for(i=begin_m;i<begin_m+max;i++)
	{
		cout<<s[i];
	}
}
int main()
{
	char s[]="I thought what I'd do was I'd pretend I am one of those deaf-mutes";	
	f(s);
	return 0;
}
