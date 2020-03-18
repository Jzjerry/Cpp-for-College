/*FunctionMap 	
				SIN=234->8;
				COS=229->3;
				TAN=227->1;
				MAX=230->4;
				MIN=228->2;
*/

#define STACK_MAX_SIZE 100

#include<iostream>
#include<cstring>
#include<cmath>



char OrderList[]="\n+-*/(),";
int Precedence_1[]={-2,1,1,3,3,0,5,-1};
int Precedence_2[]={-2,2,2,4,4,7,0,-1};
int ParNumMap[]={0,1,2,1,2,0,0,0,1};

int Hash(int Charsum)
{
	int FunctionN=0;
	FunctionN=Charsum-226; 
	return FunctionN;
}

double FunctionOut(double a,int FunctionNo)
{
	double result=0;
	switch(FunctionNo)
	{
		case 1:			//Tan
		{
			result=tan(a);
			break;
		}
		case 3:		//Cos
		{
			result=cos(a);
			break;
		}
		case 8:		//Sin
		{
			result=sin(a);
			break;
		}
		default:
		{
			std::cout<<"Function Failure--Not Found\n";
		}
	}
	return result;
}
double FunctionOut(double a,int FunctionNo,double b)
{
	double result=0;
	switch(FunctionNo)
	{
		case 2:			//Min
		{
			result=a<b?a:b;
			break;
		}
		case 4:		//Max
		{
			result=a>b?a:b;
			break;
		}
		default:
		{
			std::cout<<"Function Failure--Not Found\n";
		}
	}
	return result;
}

template<class T>
class stack
{
	public:
		T* base;
		T* top;
		unsigned int stacksize=0;
		stack(){base=new T[(STACK_MAX_SIZE)];top=base;}
		bool Push(T e);
		T Pop();
		T GetTop();
		bool Empty();
		void Clear(); 
};
bool IsOrder(char c)
{
	for(int i=0;i<strlen(OrderList);i++)
	{
		if(c==OrderList[i]) return true;
	}
	return false;
}

char Precede(char a,char b)
{
	int ia,ib;
	for(ia=0;a!=OrderList[ia];ia++);
	for(ib=0;b!=OrderList[ib];ib++);
	if(Precedence_1[ia]>Precedence_2[ib])
	{
		return '>';
	}
	else if(Precedence_1[ia]<Precedence_2[ib])
	{
		return '<';
	}
	else
	{
		return '=';
	}
}

double Caculate(double a,char od,double b)
{
	double result=0;
	switch(od)
	{
		case '+':
			result=b+a;
			break;
		case '-':
			result=b-a;
			break;
		case '*':
			result=a*b;
			break;
		case '/':
			result=b/a;
			break; 
	}
	return result;
}

int main()
{
	stack<double>DataStack;
	stack<char>OrderStack;
	stack<int>FunctionStack;
	char *c=new char[100];
	int j=0;
	std::cout<<"Expression Length Limit:100\n";
	while((c[j]=std::cin.get())!='\n')
	{
		j++;
	}
	for(int i=0;OrderStack.GetTop()!='\n';)
	{
		if(c[i]>='0'&&c[i]<='9')
		{
			double num=0;
			stack<int>intnum;
			stack<int>decnum;
			bool pointflag=1;
			while(c[i]>='0'&&c[i]<='9'||c[i]=='.')
			{
				if(c[i]=='.')
				{
					pointflag=false;
					i++;
				}
				if(pointflag)
				{
					intnum.Push(c[i]-'0');
					i++;
				}
				else
				{
					decnum.Push(c[i]-'0');
					i++;
				}
			}
			int times=0;
			while(!(intnum.Empty()))
			{
				num+=intnum.Pop()*pow(10,times);
				times++;
			}
			while(!(decnum.Empty()))
			{
				num+=decnum.Pop()*pow(0.1,1+decnum.stacksize);
			}
			DataStack.Push(num);
		}
		if(c[i]>='A'&&c[i]<='Z')
		{
			int FunNum=0;
			while(c[i]>='A'&&c[i]<='Z')
			{
				FunNum+=(int)c[i];
				i++;
			}
			FunctionStack.Push(Hash(FunNum));
		}
		if(IsOrder(c[i]))
		{
			if(OrderStack.Empty())
			{
				OrderStack.Push(c[i]);
				i++;
			}
			else
			{
				char de=Precede(OrderStack.GetTop(),c[i]);
				switch(de)
				{
					case '<':
						OrderStack.Push(c[i]);
						i++;
						break;
					case '=':
						OrderStack.Pop();
						if(!FunctionStack.Empty())
						{
							int Fuc=FunctionStack.Pop();
							if(ParNumMap[Fuc]==1)
							{
								double Par=DataStack.Pop();
								double re=FunctionOut(Par,Fuc);
								DataStack.Push(re);
							}
							else if(ParNumMap[Fuc]==2)
							{
								double Par1=DataStack.Pop();
								double Par2=DataStack.Pop();
								double re=FunctionOut(Par1,Fuc,Par2);
								DataStack.Push(re);
							}
						}
						i++;
						break;
					case '>':
						char order=OrderStack.Pop();
						double a,b;
						a=DataStack.Pop();
						b=DataStack.Pop();
						DataStack.Push(Caculate(a,order,b));
						if(c[i]==',')
						{
							i++;
						}
						break;
				}
			}
		}
	}
	std::cout<<"Result is:"<<DataStack.Pop()<<"\n";
	std::cout<<"Expression Length:"<<strlen(c)-1<<"\n";
	return 0;
} 
template<class T>
bool stack<T>::Empty()
{
	return (stacksize==0);
}


template<class T>
bool stack<T>::Push(T e)
{
	if(stacksize<=STACK_MAX_SIZE)
	{
		*top=e;
		top++;
		stacksize++;
		return true;
	}
	else return false;
}

template<class T>
T stack<T>::Pop()
{
	if(!(Empty()))
	{
		top--;
		stacksize--;
		return *top;
	}
}

template<class T>
T stack<T>::GetTop()
{
	T* prt=top;
	prt--;
	return *prt;
}

template<class T>
void stack<T>::Clear()
{
	stacksize=0;
	top=base;
	return;
}
