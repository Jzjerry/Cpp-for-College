#include<iostream>
#include<cstdlib>
#define MAXQSIZE 100

typedef int QElemType;


typedef class
{
	public:
    	QElemType *base;
    	int front;
    	int rear;
}Queue;

void InitQueue(Queue &Q)
{
    Q.base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
    if(!Q.base){std::cout<<"ERROR00:Can't initialize queue."<<std::endl;return;}
    Q.front=0;
    Q.rear=Q.front;
    return;
}

int QueueLength(Queue Q)
{
    return (Q.front-Q.rear);
}

void DestroyQueue(Queue &Q)
{
    if(!Q.base){std::cout<<"ERROR01:Queue doesn't exist."<<std::endl;return;}
    free(Q.base);
    Q.base=NULL;
    return;
}

void ClearQueue(Queue &Q)
{
    Q.front=0;
    Q.rear=Q.front;
    return;
}

bool QueueEmpty(Queue Q)
{
    return (Q.rear==Q.front);
}

QElemType GetHead(Queue Q)
{
    if(QueueEmpty(Q)){std::cout<<"ERROR01:Queue is empty."<<std::endl;return 0;}
    else return Q.base[Q.rear];
}

void EnQueue(Queue &Q,QElemType e)
{
    Q.base[Q.front++]=e;
    return;
}
void DeQueue(Queue &Q,QElemType &e)
{
    if(QueueEmpty(Q)){std::cout<<"ERROR01:Queue is empty."<<std::endl;return;}
    else
    {
        e=Q.base[Q.rear++];
        return;
    }
}
void DeQueue(Queue &Q)
{
	if(QueueEmpty(Q)){std::cout<<"ERROR01:Queue is empty."<<std::endl;return;}
	Q.rear++;
	return;
}
void QueueTraverse(Queue Q)
{
    for(int n=Q.rear;n<Q.front;n++)
    {
        std::cout<<Q.base[n]<<" ";
    }
    std::cout<<std::endl<<"Length:"<<QueueLength(Q)<<std::endl;
    return;
}
int main()
{
	int n;
	Queue Q1;
	InitQueue(Q1);
	std::cin>>n;
	for(int i=0;i<n;i++)
	{
		int e;
		std::cin>>e;
		EnQueue(Q1,e);
	}
	QueueTraverse(Q1); 
	DeQueue(Q1);
	QueueTraverse(Q1);
	ClearQueue(Q1);
	QueueTraverse(Q1);
	DestroyQueue(Q1); 
    return 0;
}
