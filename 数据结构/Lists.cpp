#include<iostream>
#include<cassert>

typedef enum{ATOM,HEAD,SUB}ElemTag;

template<class AtomType>
struct LNode
{
    ElemTag tag;
    LNode<AtomType> *next;
    union 
    {
        /* data */
        AtomType atom;
        LNode<AtomType> *sub;
    };
    LNode(ElemTag _tag=HEAD,AtomType _atom=0)
    :tag(_tag),
    atom(_atom),
    next(NULL)
    {
        if(tag==SUB)
        {
            sub=NULL;
        }
    }
};

template<class T>
class GList
{
    public:
    GList();
    GList(const char* str);
    void Print();
    size_t Length();
    size_t Depth();
    void InsertFirst(T e);
    void InsertFirst(LNode<T> e);
    bool Pop();
    GList(const GList& copy);
    GList & operator = (const GList& copy)
    {
    	GList<T>Temp(copy);
		return Temp; 
	}
    ~GList();
    
    protected:
    LNode<T>* _Head;

    void _Print(LNode<T>* Head);
    LNode<T>* _CreateGList(const char* &str);
    size_t _Length(LNode<T>* Head);
    size_t _Depth(LNode<T>* Head);
    LNode<T>* _Copy(const LNode<T>* Head);
    void _DestoryGList(LNode<T>* Head);
};

template<class T>
LNode<T>* GList<T>::_Copy(const LNode<T>* Head)
{
	LNode<T>* CHead=new LNode<T>(HEAD);
	LNode<T>* copy=CHead;
	if(Head==NULL)
	{
		return NULL;
	}
	LNode<T>* cur=Head->next;
	while(cur)
	{
		if(cur->tag==ATOM)
		{
			copy->next=new LNode<T>(ATOM,cur->atom);
			copy=copy->next;
		}
		else if(cur->tag==SUB)
		{
			copy->next=new LNode<T>(SUB);
			copy=copy->next;
			copy->sub=_Copy(cur->sub);
		}
		cur=cur->next;
	}
	return CHead;
}

template<class T>
LNode<T>* GList<T>::_CreateGList(const char* &str)
{
    assert(*str=='(');
    LNode<T>* Head=new LNode<T>(HEAD,'0');
    LNode<T>* cur=Head;
    str++;
    while(*str)
    {
        if((*str>='0'&&*str<='9')||(*str>='a'&&*str<='z')||(*str>='A'&&*str<='Z'))
        {
            cur->next=new LNode<T>(ATOM,*str);
            cur=cur->next;
        }
        else if(*str=='(')
        {
            cur->next=new LNode<T>(SUB);
            cur=cur->next;
            cur->sub=_CreateGList(str);
        }
        else if(*str==')')
        {
            return Head;
        }
        str++;
    }
    return Head;
}


template<class T>
GList<T>::GList()
{
    _Head=new LNode<T>();
}

template<class T>
GList<T>::GList(const char* str)
:_Head(NULL)
{
    _Head=_CreateGList(str);
}

template<class T>
GList<T>::GList(const GList& copy)
:_Head(NULL)
{
	_Head=_Copy(copy._Head);
}

template<class T>
GList<T>::~GList()
{
    _DestoryGList(_Head);
}


template<class T>
void GList<T>::Print()
{
    _Print(_Head);
    return;
}

template<class T>
size_t GList<T>::Length()
{
    return _Length(_Head);
}

template<class T>
size_t GList<T>::Depth()
{
    return _Depth(_Head);
}


template<class T>
void GList<T>::_Print(LNode<T>* Head)
{
    if(Head==NULL)
    {
        std::cout<<"GList is NULL\n";
        return;
    }
    LNode<T>* cur=Head;
    while(cur)
    {
        if(cur->tag==HEAD)
        {
            std::cout<<'(';
        }
        else if(cur->tag==ATOM)
        {
            std::cout<<cur->atom;
            if(cur->next)
            {
                std::cout<<',';
            }
        }
        else if(cur->tag==SUB)
        {
            _Print(cur->sub);
            if(cur->next)
            {
                std::cout<<',';
            }
        }
        cur=cur->next;
    }
    std::cout<<")";
}

template<class T>
size_t GList<T>::_Length(LNode<T>* Head)
{
    size_t count=0;
    LNode<T>* begin=Head;
    while(begin)
    {
        if(begin->tag==ATOM)
        {
            count++;
        }
        else if(begin->tag==SUB)
        {
            count+=_Length(begin->sub);
        }
        begin=begin->next;
    }
    return count;
}

template<class T>
size_t GList<T>::_Depth(LNode<T>* Head)
{
    if(_Head==NULL)
    {
        return 0;
    }
    size_t dp=0;
    LNode<T>* cur=Head;
    size_t max=0;
    while(cur)
    {
        if(cur->tag==SUB)
        {
            dp=_Depth(cur->sub);
            if(max<dp)
            {
                max=dp;
            }
        }
        cur=cur->next;
    }
    return max+1;
}

template<class T>
void GList<T>::_DestoryGList(LNode<T>* Head)
{
    if(_Head==NULL)
    {
        return ;
    }
    while(Head)
    {
        LNode<T>* begin=Head->next;
        if(Head->tag==SUB)
        {
            _DestoryGList(Head->sub);
        }
        delete Head;
        Head=begin;
    }
    return;
}

template<class T>
void GList<T>::InsertFirst(T e)
{
	LNode<T>* cur=_Head;
	LNode<T>* In=new LNode<T>(ATOM,e);
	if(!cur->next)
	{
		std::cout<<"GList is Empty\n";
		return;
	}
	cur=cur->next;
	_Head->next=In;
	In->next=cur;
	return;
}

template<class T>
void GList<T>::InsertFirst(LNode<T> e)
{
	LNode<T>* cur=_Head;
	LNode<T>* In=new LNode<T>;
	In->tag=e.tag;
	if(In->tag==HEAD)
	{
		std::cout<<"Only one Head Node is allowed\n"; 
		return;
	}
	if(In->tag==SUB)
	{
		In->sub=_Copy(e.sub);
	}
	else if(In->tag==ATOM)
	{
		In->atom=e.atom;
	}
	cur=cur->next;
	_Head->next=In;
	In->next=cur;
	return;
}

template<class T>
bool GList<T>::Pop()
{
	LNode<T>* cur=_Head;
	if(!cur->next)
	{
		std::cout<<"GList is Empty\n";
		return false;
	}
	cur=cur->next;
	_Head->next=cur->next;
	delete cur;
	return true;
}

int main()
{
	GList<char>A("(a,(b,c))");
	GList<char>B(A);
	GList<char>C=B;
	LNode<char>D(ATOM,'D');
	std::cout<<A.Depth()<<" "<<A.Length()<<"\n";
	A.Print();
	B.Pop();
	//std::cout<<"\n"<<B.Depth()<<" "<<B.Length()<<"\n";
	B.Print();
	std::cout<<"\n";
	C.InsertFirst(D);
	C.Print();
	return 0;
}
