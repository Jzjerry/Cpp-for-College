#include<iostream>
#include<exception>
#include<cstring>
#include<fstream>
#include<vector>

char **_HuffmanCode;
char *Dictionary;

int main()
{
	std::ifstream read;
	std::ofstream decode;
	read.open("Huffman.dat",std::ios::in);
	decode.open("Huffbaby.back",std::ios::out);
	size_t n;
	read>>n;
	_HuffmanCode=new char*[n];
	Dictionary=new char[n];
	for(int i=1;i<=n;i++)
	{
		read>>Dictionary[i];
		char ch;
		int ptr=0;
		_HuffmanCode[i]=new char[100]; 
		while((ch=read.get())!='\n')
		{
			_HuffmanCode[i][ptr]=ch;
			ptr++;
		}
		_HuffmanCode[i][ptr]='\0';
	}
	std::vector<int> match;
    int ptr=0;
    char ch;
	while((ch=read.get())!=EOF)
	{
    	if(ptr==0)
		{ 
    		for(int j=1;j<=n;j++)
    		{
    			if(_HuffmanCode[j][ptr]==ch)
    			{
    				match.insert(match.begin(),j);
				}
			}
			ptr++;
		}
		else
		{
			std::vector<int>::iterator k=match.begin();
			while(k!=match.end())
			{
				if(_HuffmanCode[*k][ptr]!=ch)
				{
					match.erase(k);
				}
				else
				{
					k++;
				}
			}
			if(match.size()==1)
			{
				decode<<Dictionary[*match.begin()];
				match.clear();
				for(int i=1;i<=strlen(_HuffmanCode[*match.begin()])-1-ptr;i++)
				{
					ch=read.get();
				}
				ptr=0;
			}
			else
			{
				ptr++;
			}
		}
	}
	read.close();
	decode.close();
	return 0;
}
