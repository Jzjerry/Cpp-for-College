#include<iostream>
#define MAX_DIM 10

/*用了C++11的可变参数模板写法 
和va_list版本没有太大区别*/ 

void Error()
{
    std::cout<<"Error"<<std::endl;
    return ;
}

template<class ElemType>
struct Array
{
    public:
	ElemType *base;
    int dim;
    int *bounds;
    int *constants;
    template<typename...T>
    Array(int d,T...args):dim(d),bounds(new int[sizeof...(args)]{args...})
    {
        if(d<0||d>MAX_DIM) Error();
        else
        {
            int elemtotal=1;
            for(int i=0;i<dim;++i)
            {
                elemtotal*=bounds[i];
            }
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
    template<typename...T>
    bool Locate(int &off,T...args)
    {
        off=0;
        int ind[]={args...,0};
        for(int i=0;i<dim;++i)
        {
            if(ind[i]<0||ind[i]>bounds[i]) 
			{Error(); return false;}
            off+=constants[i]*ind[i];
        }
        return true;
    }
    template<typename...T>
    bool Value(ElemType &e,T...args)
    {
        int result;
        int off;
        if((result=(Locate(off,args...))<=0)) return result;
        e=*(base+off);
        return true;
    }
    template<typename...T>
    bool Assign(ElemType e,T...args)
    {
        int result;
        int off;
        if((result=Locate(off,args...))<=0) return result;
        *(base+off)=e;
        return true;
    }
};


int main()
{
	Array<int>A(3,50,40,30);
	int e;
	A.Assign(10,24,24,24);
	A.Value(e,24,24,24);
	std::cout<<e<<std::endl; 
    return 0;
}
