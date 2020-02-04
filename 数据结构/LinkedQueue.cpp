#include<iostream>
#include<cstdlib>

typedef int QElemType;

typedef class QNode
{
    public:
    	QElemType data;
        QNode *next;
        QNode(){};
        QNode(int e,QNode *p){data=e;next=p;}
}QNode,*QPrt;

typedef class LinkQueue
{
    protected:
        QPrt front;
        QPrt rear;
    public:
    LinkQueue()
    {
        front=(QPrt)malloc(sizeof(QNode));rear=front;
        if(!front){std::cout<<"ERROR";}
        front->next=NULL;
    }
    ~LinkQueue()
    {
        while(front)
        {
            rear=front->next;
            free(front);
            front=rear;
        }
    }
    void EnQueue(const QElemType e)
    {
        QPrt p;
        p=(QPrt)malloc(sizeof(QNode));
        if(!p){std::cout<<"ERROR";}
        p->data=e;
        p->next=NULL;
        rear->next=p;
        rear=p;
        return;
    }
    void DeQueue(QElemType &e)
    {
    	QPrt p;
        if(front==rear){std::cout<<"ERROR";}
        p=front->next;
        e=p->data;
        front->next=p->next;
        if(rear==p){rear=front;};
        free(p);
        return;
    }
    void QueueTraverse()
    {
    	if(front==rear){std::cout<<"Empty"<<std::endl;return;}
    	QPrt p=front->next;
    	while(p)
    	{
    		std::cout<<p->data<<" ";
    		p=p->next;
		}
		return;
	}
	void ClearQueue()
	{
		QElemType b;
		while(rear!=front)
		{
			DeQueue(b);
		}
		return;
	}
	QElemType Head()
	{
		if(front==rear){std::cout<<"Empty"<<std::endl;return -1;}
		QPrt p=front->next;
		return p->data;
	}
	int Length()
	{
		if(front==rear){std::cout<<"Empty"<<std::endl;return 0;}
		QPrt p=front->next;
		int n=0;
		while(p)
		{
			n++;
			p=p->next;
		}
		return n;
	}
	bool ifEmpty()
	{
		return (front==rear);
	}
}LinkQueue;

int main()
{
	LinkQueue A;
	QElemType b;
	A.EnQueue(1);
	A.EnQueue(2);
	A.EnQueue(3);
	std::cout<<"Head:"<<A.Head()<<" Length:"<<A.Length()<<std::endl<<"Traverse:";
	A.QueueTraverse();
	A.ClearQueue();
	if(A.ifEmpty()){std::cout<<"Empty"<<" ";}
	A.QueueTraverse();
	return 0;
}

