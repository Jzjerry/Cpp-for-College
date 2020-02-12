#include<iostream>
#include<cstdarg>
#define MAX_DIM 10

/*这应该是所有里面写的最乱的一个 
  因为我以前从来没有用过va_list*/ 

void Error()
{
    std::cout<<"Error"<<std::endl;
    return ;
}

template<class ElemType>
struct Array
{
	protected:
	va_list ap;
    public:
	ElemType *base;
    int dim;
    int *bounds;
    int *constants;
    Array(int d,...)
    {
        if(d<0||d>MAX_DIM) Error();
        else
        {
            int elemtotal=1;
            dim=d;
            bounds=new int[dim];
            va_start(ap,d);
            for(int i=0;i<dim;++i)
            {
                bounds[i]=va_arg(ap,int);
                elemtotal*=bounds[i];
            }
            va_end(ap);
            base=new ElemType[elemtotal];
            constants=new int[dim];
            constants[dim-1]=1;
            for(int i=dim-2;i>=0;--i)
            {
                constants[i]=bounds[i+1]*constants[i+1];
            }
        }
    }
    ~Array()
    {
        if(!base){Error();}
        else {delete base;base=NULL;}
        if(!bounds){Error();}
        else{delete bounds;bounds=NULL;}
        if(!constants){Error();}
        else{delete constants;constants=NULL;}
    }
    bool Locate(int &off,...)
    {
        off=0;
        for(int i=0;i<dim;++i)
        {
        	int ind;
            ind=va_arg(ap,int);
            if(ind<0||ind>bounds[i]) 
			{Error(); return false;}
            off+=constants[i]*ind;
        }
        return true;
    }
    bool Value(ElemType &e,...)
    {
        int result;
        int off;
        va_start(ap,e);
        if((result=(Locate(off))<=0)) return result;
        e=*(base+off);
        return true;
    }
    bool Assign(ElemType e,...)
    {
        int result;
        int off;
        va_start(ap,e);
        if((result=Locate(off))<=0) return result;
        *(base+off)=e;
        return true;
    }
};


int main()
{
	Array<int>A(2,50,50);
	int e;
	A.Assign(10,24,24);
	A.Value(e,24,24);
	std::cout<<e<<std::endl; 
    return 0;
}
