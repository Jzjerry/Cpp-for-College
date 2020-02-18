/*Ultra Shitty Mountain with Ultra Shitty Addition&Subtraction*/

#include<iostream>
#define MAX_SIZE 12500

template<class ElemType>
ElemType max(ElemType a,ElemType b)
{
    return a>b?a:b;
}
template<class ElemType>
ElemType min(ElemType a,ElemType b)
{
    return a>b?b:a;
}

template<class ElemType>
struct TriElem
{
    int i,j;
    ElemType e;
    TriElem(){}
    TriElem(int a,int b,ElemType c):i(a),j(b),e(c){}
};


template<class ElemType>
struct Matrix
{
    TriElem<ElemType>*data;
    int mu=0,nu=0,tu;
    int *rpos;
    Matrix(){}
    void set_rpos()
    {
    	rpos=new int[mu+1];
        for(int i=1;i<=mu;i++)
        {
        	rpos[i]=tu+1;
		}
        for(int k=1;k<=tu;k++)
        {
        	rpos[data[k].i]=min(k,rpos[data[k].i]);
		}
		for(int j=1;j<mu;j++)
        {
        	int l=j+1;
        	while(rpos[j]==tu+1)
        	{
        		if(l<mu&&rpos[l]!=tu+1) rpos[j]=rpos[l];
        		else if(l==mu) { rpos[j]=rpos[l]; break;}
        		else l++;
        	}
		}
		return;
	}
    void AssignMatrix()
    {
    	data=new TriElem<ElemType>[tu+1];
        for(int i=1;i<=tu;i++)
        {
            int x,y;
            ElemType e;
            std::cin>>x>>y>>e;
            data[i].i=x;
            data[i].j=y;
            data[i].e=e;
			mu=max(x,mu);
            nu=max(y,nu);
            /*
            mu=max(nu,mu);
            nu=mu;
            */
        }
        set_rpos();
    	return;
	}
    Matrix(int n=0):tu(n)
    {
		AssignMatrix(tu);
    }
    Matrix(int t,int m,int n):tu(t),mu(m),nu(n)
	{
		data=new TriElem<ElemType>[MAX_SIZE+1];
		rpos=new int[mu+1]{0};
	}
    Matrix Transpose()
    {
        Matrix<ElemType>T(tu,nu,mu);
        if(T.tu)
        {
            int q=1;
            for(int col=1;col<=nu;col++)
            {
                for(int p=1;p<=tu;p++)
                {
                	if(data[p].j==col)
                    {
						T.data[p].e=data[p].e;
                    	T.data[p].i=data[p].j;
                    	T.data[p].j=data[p].i;
                    	q++;
            		}
				}
            }
        }
        return T;
    }
    Matrix FastTranspose()
    {
    	Matrix<ElemType>T(tu,nu,mu);
    	int *num=new int[nu+1];
        for(int i=1;i<=nu;i++)
        {
        	num[i]=0;
		}
        for(int i=1;i<=tu;i++)
    	{
    		num[data[i].j]++;
		}
    	int cpot[nu];
    	if(T.tu)
    	{
			cpot[1]=1;
			for(int col=2;col<=nu;col++)
			{
				cpot[col]=cpot[col-1]+num[col-1]; 
			}
			for(int p=1;p<=tu;p++)
			{
				int col=data[p].j;
				int q=cpot[col];
				T.data[q].i=data[p].j;
				T.data[q].j=data[p].i;
				T.data[q].e=data[p].e;
				cpot[col]++;
			}
		}
		return T; 
	}
    inline void operator =(const Matrix T) 
    {
    	tu=T.tu;
    	mu=T.mu;
    	nu=T.nu;
    	data=new TriElem<ElemType>[tu+1];
		for(int i=1;i<=tu;i++)
		{
			data[i]=T.data[i];
		}
		rpos=new int[mu+1];
		for(int i=1;i<=mu;i++)
		{
			rpos[i]=T.rpos[i];
		}
		return;
	}
	inline Matrix operator *(const Matrix T)const
	{
		if(nu!=T.mu&&(tu*T.tu!=0))
		{
			std::cout<<"invalid multiply\n";
			return *this;
		}
		else
		{
			Matrix<int>M(0,mu,T.nu);
			for(int arow=1;arow<=mu;arow++)
			{
				ElemType ctemp[M.nu+1]={0};
				int tp=0;
				M.rpos[arow]=M.tu+1;
				if(arow<mu) tp=rpos[arow+1];
				else tp=tu+1;
				for(int p=rpos[arow];p<tp;p++)
				{
					int brow=data[p].j;
					int t=0;
					if(brow<T.mu) t=T.rpos[brow+1];
					else t=T.tu+1;
					for(int q=T.rpos[brow];q<t;q++)
					{
						int ccol=T.data[q].j;
						ctemp[ccol]+=data[p].e*T.data[q].e;
					}
				}
				for(int ccol=1;ccol<=M.nu;ccol++)
				{
					if(ctemp[ccol])
					{
						M.tu++;
						TriElem<ElemType>N(arow,ccol,ctemp[ccol]);
						M.data[M.tu]=N;
					}
				}
			}
			M.set_rpos();
			return M;
		}
	}
	inline Matrix operator +(const Matrix T)const
	{
		if(mu!=T.mu||nu!=T.nu){std::cout<<"invalid addition\n";return *this;}
		else
		{
			Matrix<ElemType>Sum(0,mu,nu);
			int k=1;
			int l=1;
			while(k<=tu||l<=T.tu)
			{
				if(data[k].i==T.data[l].i)
				{
					if(data[k].j==T.data[l].j)
					{
						if(data[k].e+T.data[l].e)
						{
							Sum.tu++;
							TriElem<ElemType>A(data[k].i,data[k].j,data[k].e+T.data[l].e);
							Sum.data[Sum.tu]=A;
						}
						k++;
						l++;
					}
					else
					{
						if(data[k].j<T.data[l].j)
						{
							Sum.tu++;
							TriElem<ElemType>A(data[k].i,data[k].j,data[k].e);
							Sum.data[Sum.tu]=A;
							k++;
						}
						else if(data[k].j>T.data[l].j)
						{
							Sum.tu++;
							TriElem<ElemType>A(T.data[l].i,T.data[l].j,T.data[l].e);
							Sum.data[Sum.tu]=A;
							l++;
						}
					}
				}
				else
				{
					while(data[k].i<T.data[l].i)
					{
						Sum.tu++;
						TriElem<ElemType>A(data[k].i,data[k].j,data[k].e);
						Sum.data[Sum.tu]=A;
						k++;
					}
					while(data[k].i>T.data[l].i)
					{
						Sum.tu++;
						TriElem<ElemType>A(T.data[l].i,T.data[l].j,T.data[l].e);
						Sum.data[Sum.tu]=A;
						l++;
					}
				}
			}
			Sum.set_rpos();
			return Sum;
		}	
	}
	inline Matrix operator -(const Matrix T)const
	{
		if(mu!=T.mu||nu!=T.nu){std::cout<<"invalid Sutraction\n";return *this;}
		else
		{
			Matrix<ElemType>Sub(0,mu,nu);
			int k=1;
			int l=1;
			while(k<=tu||l<=T.tu)
			{
				if(data[k].i==T.data[l].i)
				{
					if(data[k].j==T.data[l].j)
					{
						if(data[k].e-T.data[l].e)
						{
							Sub.tu++;
							TriElem<ElemType>A(data[k].i,data[k].j,data[k].e-T.data[l].e);
							Sub.data[Sub.tu]=A;
						}
						k++;
						l++;
					}
					else
					{
						if(data[k].j<T.data[l].j)
						{
							Sub.tu++;
							TriElem<ElemType>A(data[k].i,data[k].j,data[k].e);
							Sub.data[Sub.tu]=A;
							k++;
						}
						else if(data[k].j>T.data[l].j)
						{
							Sub.tu++;
							TriElem<ElemType>A(T.data[l].i,T.data[l].j,-T.data[l].e);
							Sub.data[Sub.tu]=A;
							l++;
						}
					}
				}
				else
				{
					while(data[k].i<T.data[l].i)
					{
						Sub.tu++;
						TriElem<ElemType>A(data[k].i,data[k].j,data[k].e);
						Sub.data[Sub.tu]=A;
						k++;
					}
					while(data[k].i>T.data[l].i)
					{
						Sub.tu++;
						TriElem<ElemType>A(T.data[l].i,T.data[l].j,-T.data[l].e);
						Sub.data[Sub.tu]=A;
						l++;
					}
				}
			}
			Sub.set_rpos();
			return Sub;
		}	
	}
    void Print()
    {
        int col=1;
        for(int i=1;i<=mu;i++)
        {
            for(int j=1;j<=nu;j++)
            {
                if((data[col].i==i)&&(data[col].j==j)&&(col<=tu))
				{std::cout<<data[col].e<<" ";col++;}
                else{std::cout<<0<<" ";}
            }
            std::cout<<"\n";
        }
        return;
    }
};



int main()
{
	int n=0;
	//std::cin>>n;
    Matrix<int>A(4,4,4);
    A.AssignMatrix();
    std::cout<<"\n";
    A.Print();
    Matrix<int>B(8,4,4);
    B.AssignMatrix();
    std::cout<<"\n";
    B.Print();
    std::cout<<"\n";
    Matrix<int>C=B-A;
    C.Print();
    std::cout<<"\n";
    C=C*C;
    C=C*C;
    std::cout<<"\n";
    C.Print();
    std::cout<<"\n";
    for(int i=1;i<=C.mu;i++)
	{
		std::cout<<C.rpos[i]<<" ";
	}
    return 0;
}
