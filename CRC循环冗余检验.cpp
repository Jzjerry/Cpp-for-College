/*CRC循环冗余的手写实现
使用int类型来存储传输的数据
不使用rand()函数的写法为理想情况的校验准确度分析
使用rand()函数的写法为非理想情况
*/
#include<iostream>
#include<bitset>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<fstream>

inline int BinLength(int a)
{
	int Length=0;
	while(a)
	{
		a/=2;
		Length++;
	}
	return Length;
}


int BinMod(int a,int b)
{
	while(BinLength(a)>=BinLength(b))
	{
		a=a^(b<<(BinLength(a)-BinLength(b)));
	}
	return a;
}


class Frame
{
	private:
		unsigned int Length=0;
	protected:
		unsigned int _CheckSq=0;
		unsigned int _CheckP=0;
		unsigned int _CheckLength=0;
	public:
		unsigned noise=0;
		unsigned int Data;
		Frame(){Data=0;Length=0;}
		Frame(int a)
		:Data(a)
		{
			Length=BinLength(Data);
		}
		bool CRC_On(int P,int L)
		{
			int a=0;			
			_CheckP=P;
			_CheckLength=L;		
			Length+=_CheckLength;
			Data=Data<<_CheckLength;
			_CheckSq=BinMod(Data,_CheckP);
			if((double)_CheckSq<=(pow(2,_CheckLength)-1))
			{
				Data+=_CheckSq;
				return true;
			}
			else return false;
		}
		bool CRC_Off()
		{
			if(_CheckP&&_CheckSq)
			{	
				Data-=_CheckSq;
				Length-=_CheckLength;
				Data=Data>>_CheckLength;
				_CheckP=0;
				_CheckSq=0;
				_CheckLength=0;
				return true;
			}
			else return false;
		}
		void Output()
		{
			std::cout<<std::bitset<16>(Data)<<"\n";
			return;
		}
		void Noise()
		{
			//srand((unsigned)time(NULL));
			//noise=(int)rand()%(int)(pow(2,Length)-1);
			Data+=noise;
			return;
		}	
	bool Error_Check()
	{
		return (!BinMod(Data,_CheckP));
	}
};

int main()
{
	int n;
	int rdata=0;
	int rq=0; 
	double acount=0;
	double fcount=0;
	std::cin>>n>>rq;
	std::ofstream outfile;
	outfile.open("Error.txt",std::ios::out|std::ios::trunc);
	outfile<<"Frame Divisor: "<<rq<<"\n\n";
	for(int i=1;i<=n;i++)
	{
		//srand((unsigned)i+(unsigned)time(NULL));
		rdata=250;
		Frame Deliver(rdata);
		Deliver.Output();
		if(Deliver.CRC_On(rq,3))
		{
			Deliver.noise=i%16;
			Deliver.Output();
			Deliver.Noise();
			Deliver.Output();
			if(Deliver.Error_Check())
			{
				std::cout<<"Accepted\n";
				if(Deliver.noise)
				{ 
					acount++;
					outfile<<"Accpeted In Case: No."<<i<<"\n";
					outfile<<"Frame data: "<<std::bitset<8>(rdata)<<"\n"; 
					//outfile<<"Frame Divisor: "<<std::bitset<8>(rq)<<"\n";
					outfile<<"Noise: "<<std::bitset<8>(Deliver.noise)<<"\n\n";
				} 
			}
			else
			{
				std::cout<<"Denied\n";
			}
		}
	}
	std::cout<<"Accuracy:"<<std::setprecision(6)<<1.0-acount/((double)n-fcount)<<"\n";
	//Deliver.CRC_Off();
	return 0;
}
