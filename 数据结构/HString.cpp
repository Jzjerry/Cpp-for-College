#include<iostream>
#include<cstdlib>

typedef class HString
{
    public:
        char *ch;
        int length;
        HString(){ch=NULL;length=0;}
        inline void operator =(const char *chars)
        {
            int i=0;
            char c=chars[0];
            if(ch) free(ch);
            while(c)
            {
            	c=chars[++i];
			}
            if(!i)
            {
                ch=NULL;
                length=0;
            }
            else
            {
                ch=(char*)malloc((i)*sizeof(char));
                for(int a=0;a<i;a++)
                {
                ch[a]=chars[a];
                }
                ch[i]='\0';
               length=i;
            }
        }
        inline HString operator +(const HString& S)const
        {
            HString Sum;
            int i=0;
            Sum.length=length+S.length;
            Sum.ch=(char*)malloc((Sum.length)*sizeof(char));
            for(i=0;i<length;i++)
            {
                Sum.ch[i]=ch[i];
            }
            for(i;i<Sum.length;++i)
            {
                Sum.ch[i]=S.ch[i-length];
            }
            Sum.ch[i]='\0';
            return Sum;
        }
		int StrLength(HString S){return S.length;}
        void ClearString()
        {
            if(ch){free(ch);ch=NULL;}
            length=0;
            return;
        }
        HString SubString(int pos,int len)
        {
        	HString S;
        	S.ClearString();
        	if(pos<0||pos>length-1||len<1||len>length-pos)
        	{
        		std::cout<<"ERROR"<<std::endl; 
        		return S;
			}
			else
			{
				S.ch=(char*)malloc((len+1)*sizeof(char));
				S.length=len;
				for(int i=0;i<len;i++)
				{
					S.ch[i]=ch[pos+i];
				}
			}
			return S;
		}
        int IndexFirst(HString T,int pos)
        {
            int i=pos;
            int j=0;
            while(i<length&&j<T.length)
            {
                if(ch[i]==T.ch[j])
                {
                    i++;
                    j++;
                }
                else
                {
                    i=i-j+1;
                    j=0;
                }
            }
            if(j==T.length) return i-T.length;
            else return 0;
        }
        int* IndexAll(HString T,int pos)
        {
            int i=pos;
            int j=0;
            int *index;
            int count=0;
            index=(int*)malloc(length*sizeof(int));
            for(int k=0;k<length;k++)
            {
            	index[k]=-1;
			}
            while(i<length)
			{ 
				while(j<T.length)
            	{
              	  if(ch[i]==T.ch[j])
            	    {
            	        i++;
            	        j++;
           		    }
            	    else
           	   		{ 
                    	i=i-j+1;
                    	j=0;
                	}
            	}
            	if(j==T.length)
            	{
            		index[count]=i-T.length;
            		count++;
            		j=0; 
				}
			} 
            return index;
        }
}HString;
int StrCompare(HString S,HString T)
{
    for(int i=0;i<S.length&&i<T.length;i++)
    {
        if(S.ch[i]!=T.ch[i])
        return S.ch[i]-T.ch[i];
    }
    return S.length-T.length;
}
int main()
{
	HString T;
	HString B;
	int i=0;
	T="AABBCCAA";
	B="A";
	std::cout<<T.length<<" ";
	std::cout<<B.length<<" ";
	T=T+B;
	std::cout<<T.ch<<" "<<T.length<<std::endl; 
	//T=T.SubString(0,5)+T.SubString(6,6);
	std::cout<<T.ch<<" "<<T.length<<" ";
	while(T.IndexAll(B,0)[i]+1)
	{
    	std::cout<<T.IndexAll(B,0)[i]<<" ";
    	i++;
    }
	return 0;
}
