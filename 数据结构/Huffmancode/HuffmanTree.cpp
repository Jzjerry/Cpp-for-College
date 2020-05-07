#include<iostream>
#include<exception>
#include<cstring>
#include<fstream>
#include<vector>

int CharStatic[26]={0};

template<class ElemType>
struct TreeNode
{
    ElemType data;
    unsigned int weight;
    unsigned int parent,lchild,rchild;
    TreeNode()
    {
        parent=0;
        lchild=0;
        rchild=0;
    }
};

template<class ElemType>
class HuffmanTree
{
    private:
    TreeNode<ElemType> *_Head;
    char **_HuffmanCode;
    size_t _ElemNum=0;
    public:
    size_t Root;
    int rootweight=0;
    HuffmanTree()
    {
    	Root=0;
        _Head=NULL;
        _HuffmanCode=NULL;
    }
    HuffmanTree(size_t n);
    void Traverse(unsigned int start)
    {
    	if(_Head==NULL) throw "Tree is Empty";
		if(_Head[start].data==0)
    	{
    		std::cout<<"0\n";
		}
		else
		{
    		std::cout<<_Head[start].data<<"\n";
    	}
    	if(_Head[start].lchild==0&&_Head[start].rchild==0)
    	{
			return;
		}
		else
		{
			if(_Head[start].lchild!=0) 	Traverse(_Head[start].lchild);
			if(_Head[start].rchild!=0)	Traverse(_Head[start].rchild);
		}
	}
	void HuffmanCodePrint(std::ostream &out)
	{
		out<<_ElemNum<<std::endl;
		for(int i=1;i<=_ElemNum;i++)
		{
			out<<_Head[i].data<<_HuffmanCode[i]<<std::endl; 
		}
		return;
	}
    inline char* HuffmanCoding(char in)
    {
        int i=0;
        while(i<=_ElemNum)
        {
        	i++;
        	if(_Head[i].data==in)
        	{
        		return _HuffmanCode[i];
			}
		}
        return "";
    }
    char* HuffmanDecoding(char* str);
    protected:
    void _Select(int n,unsigned int &s1,unsigned int &s2)
    {
        TreeNode<ElemType> *p=_Head;
        int min1,min2;
        min1=25565;
        min2=25565;
        for(int i=1;i<=n;i++)
        {
            if(p[i].parent==0)
            {
                if(p[i].weight<min1)
                {
                	s2=s1;
                    s1=i;
                    min2=min1;
                    min1=p[i].weight;
                }
                else if(p[i].weight<=min2)
                {
                    s2=i;
                    min2=p[i].weight;
                }
            }
        }
        return;
    }
};

template<class ElemType>
HuffmanTree<ElemType>::HuffmanTree(size_t n):Root(2*n-1),_ElemNum(n) 
{
	//Build HuffmanTree//
    if(n<=1){throw "Too Short";}
    size_t m=2*n-1;
    TreeNode<ElemType> *p;
    int i;
    int j=1;
    _Head=new TreeNode<ElemType>[m+1];
    for(i=1;i<=n;i++)
    {
    	ElemType d;
    	unsigned int w;
    	while(CharStatic[j]==0)
    	{
    		j++;
		}
		_Head[i].data=96+j;
		_Head[i].weight=CharStatic[j];
		j++;
    }
    for(;i<=m;i++,p++)
    {
        _Head[i].data=0;
       	_Head[i].weight=0;
    }
    for(i=n+1;i<=m;i++)
    {
        unsigned int n1,n2;
        _Select(i-1,n1,n2);
        _Head[n1].parent=i;
        _Head[n2].parent=i;
        _Head[i].lchild=n1;
        _Head[i].rchild=n2;
        _Head[i].weight=_Head[n1].weight+_Head[n2].weight;
    }
    rootweight=_Head[m].weight;
    //Genarate HuffmanCode//
    _HuffmanCode=new char*[n+1];
    char *cd=new char[n];
    cd[n-1]='\0';
    for(int i=1;i<=n;i++)
    {
    	int start=n-1;
    	int p=_Head[i].parent;
    	for(int j=i;p!=0;j=p,p=_Head[p].parent)
    	{
    		if(_Head[p].lchild==j) cd[--start]='0';
    		else cd[--start]='1';
		}
		_HuffmanCode[i]=new char[n-start];
		strcpy(_HuffmanCode[i],&cd[start]);
	}
	delete cd;
}
int main()
{
	std::ifstream PrimaryFile;
	std::ofstream EncodedFile;
		
	PrimaryFile.open("Huffboy.txt",std::ios::in);
	
	char in;
	int count=0;
	
	while((in=PrimaryFile.get())!=EOF)
	{
		if(in>=97&&in<=122)
		{
			if(CharStatic[in-96]==0) count++;
			CharStatic[in-96]++;
		}
	}
	HuffmanTree<char> Tree(count);
	PrimaryFile.clear();
    PrimaryFile.seekg(0,std::ios::beg);
    EncodedFile.open("Huffman.dat",std::ios::out);
    Tree.HuffmanCodePrint(EncodedFile);
	while((in=PrimaryFile.get())!=EOF)
    {
        EncodedFile<<(Tree.HuffmanCoding(in));
    }
    PrimaryFile.close();
    EncodedFile.close();
    /*PrimaryFile.open("Huffman.dat",std::ios::in);
    EncodedFile.open("Huffoldman.back",std::ios::out);
    char Decode[]="0111111000111110010111100101010110011010000";
    char *output;
    output=Tree.HuffmanDecoding(Decode);
    Tree.HuffmanCodePrint();
	std::cout<<output<<"\n";
    PrimaryFile.close();
    EncodedFile.close();
    */
    
    //Tree.Traverse(Tree.Root);
	//std::cout<<Tree.rootweight<<std::endl;
	return 0;
}


template<class T> 
char* HuffmanTree<T>::HuffmanDecoding(char* str)
    {
    	std::vector<int> match;
    	int ptr=0;
    	char* decode=new char[100];
    	int decodenum=0;
    	for(int i=0;i<strlen(str);i++)
    	{
    		if(ptr==0)
			{ 
    			for(int j=1;j<=_ElemNum;j++)
    			{
    				if(_HuffmanCode[j][ptr]==str[i])
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
					if(_HuffmanCode[*k][ptr]!=str[i])
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
					decode[decodenum]=_Head[*match.begin()].data;
					match.clear();
					i+=strlen(_HuffmanCode[*match.begin()])-1-ptr;
					ptr=0;
					decodenum++;
				}
				else
				{
					ptr++;
				}
			}
		}
		decode[decodenum]='\0';
		return decode;
	}
