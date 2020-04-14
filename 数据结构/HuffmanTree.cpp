#include<iostream>
#include<exception>
#include<cstring>

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
	void HuffmanCodePrint()
	{
		for(int i=1;i<=_ElemNum;i++)
		{
			std::cout<<_HuffmanCode[i]<<std::endl; 
		}
		return;
	}
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
    _Head=new TreeNode<ElemType>[m+1];
    for(i=1;i<=n;i++)
    {
    	ElemType d;
    	unsigned int w;
        std::cin>>d>>w;
        _Head[i].data=d;
        _Head[i].weight=w;
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
	HuffmanTree<char> Tree(4);
	Tree.Traverse(Tree.Root);
	std::cout<<Tree.rootweight<<std::endl;
	Tree.HuffmanCodePrint();
	return 0;
}
