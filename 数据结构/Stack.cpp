#include<iostream>
#include<cstdlib>

#define STACK_INIT_SIZE 100 
#define STACKINCREMENT 10

typedef class
{
    public:
        int *base;
        int *top;
        int stacksize;
}SqStack;

void InitStack(SqStack &S)
{
    S.base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!S.base) {std::cout<<"ERROR00:Can't initialize stack.";return;}
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return;
}
void DestoryStack(SqStack &S)
{
    free(S.top);
    S.top=NULL;
    free(S.base);
    S.base=NULL;
    S.stacksize=0;
    return;
}
bool EmptyStack(SqStack &S)
{
    return (S.base==S.top);
}
int StackLength(SqStack S)
{
	int n=0;
	while(S.top--!=S.base)
	{
		n++;
	}
    return n;
}
int GetTop(SqStack S)
{
    if(S.top==S.base) {std::cout<<"ERROR01:Stack is Empty";return -114514;}
    return *(S.top-1);
}
void Push(SqStack &S,int e)
{
    if(S.top-S.base>=S.stacksize)
    {
        S.base=(int*)malloc((S.stacksize+STACKINCREMENT)*sizeof(int));
        if(!S.base) {std::cout<<"ERROR00:Can't initialize stack.";return;}
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top=e;
    S.top++;
    return;
}
void Pop(SqStack &S,int &e)
{
    if(S.top==S.base) {std::cout<<"ERROR01:Stack is Empty";return;}
    e=*(--S.top);
    return;
}
void ClearStack(SqStack &S)
{
    S.top=S.base;
    return;
}
void StackTraverse(SqStack S)
{
    int *prt;
    prt=S.top;
    if(!EmptyStack(S))
    {
    	prt--;
        while(prt>=S.base)
        {
            std::cout<<*prt<<std::endl;
            prt--;
        }
    }
    return;
}

int main()
{
	SqStack S1;
	int n;
	int m;
	InitStack(S1);
	std::cin>>n;
	while(n--)
	{
		int e;
		std::cin>>e;
		Push(S1,e);
	}
	StackTraverse(S1);
	std::cout<<"Length:"<<StackLength(S1)<<std::endl;
	std::cout<<"Top:"<<GetTop(S1)<<std::endl;
	Pop(S1,m);
	std::cout<<"Top(after Pop):"<<GetTop(S1)<<std::endl;
	Push(S1,m);
	std::cout<<"Top(after Push):"<<GetTop(S1)<<std::endl;	
	ClearStack(S1);
	StackTraverse(S1);
	std::cout<<"Length(after Clear):"<<StackLength(S1)<<std::endl;
	return 0;
}
