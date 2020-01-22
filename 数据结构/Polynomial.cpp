#include<iostream>
#include<cstdlib>
#include<algorithm>

typedef class Node
{
    public:
    int coef;
    int expn;
    Node *next;
    Node(){}
    Node(int a,int b){coef=a;expn=b;}
    Node* operator +(Node* A);
}Polynode,*Polynomial;
int cmp(int a,int b)
{
	return a>b?1:0;
}
int PolynLength(Polynomial &P);
void PrintPolyn(Polynomial &P);
void AddPolyn(Polynomial &A,Polynomial &B);
Polynomial PolynFront(Polynomial &P,Polynomial &pn)
{
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return NULL;}
	Polynomial pf=P; 
	while(pf->next!=pn&&pf->next)
	{
		pf=pf->next;
	}
	return pf;
}
void SwapPolyn(Polynomial &P,Polynomial A,Polynomial B)
{
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	Polynomial P1=PolynFront(P,A);
	Polynomial P2=PolynFront(P,B);
	Polynomial Pt;
	P1->next=B;
	P2->next=A;
	Pt=A->next;
	A->next=B->next;
	B->next=Pt;
	return; 
}
Polynomial LocatePolyn(Polynomial &P,int i)
{
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return NULL;}
	Polynomial Pl=P;
	while(i--&&Pl)
	{
		Pl=Pl->next;
	}
	return Pl;
}
void DeletePolyn(Polynomial &P,Polynomial &A)
{
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	Polynomial Pf=PolynFront(P,A);
	if(A->next==NULL)
	{
		Pf->next=NULL; 
	}
	else
	{
		Pf->next=A->next;
	}
	return;
}
void DestroyPolyn(Polynomial &P)
{
	Polynomial pd;
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	while(P)
	{
		pd=P->next;
		free(P);
		P=pd;
	}
	P=NULL;
	return;
}//DestroyPolyn
void MergePolyn(Polynomial &P)
{
	Polynomial pm;
	Polynomial pn;
	Polynomial pt;
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	pm=P->next;
	while(pm)
	{
		pn=pm;
		while(pn)
		{
			pt=pn;
			pn=pn->next;
			if(pn&&pm->expn==pn->expn)
			{
				pm->coef=pm->coef+pn->coef;
				if(pn->next==NULL)
				{	
					pt->next=NULL;
					break; 
				}
				else
				{
					pt->next=pn->next;
				}
				free(pn);
				pn=pt;
			}
		}
		pm=pm->next;
	}
	return;
}//MergePolyn
void SortPolyn(Polynomial &P)
{
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	Polynomial Ph=P->next;
	if(!(Ph)) return;
	Polynomial Pt;
	while(Ph)//Bubble_Sort
	{
		Pt=Ph->next;
		while(Pt)
		{
			if(cmp(Ph->expn,Pt->expn))
			{
				//PrintPolyn(P);
				//SwapPolyn(P,Ph,Pt);//Need Correction
				std::swap(Ph->expn,Pt->expn);
				std::swap(Ph->coef,Pt->coef); 
			}
			Pt=Pt->next;
		}
		Ph=Ph->next;
	}
	return;
}
void CreatePolyn(Polynomial &P,int n)
{
	Polynomial pn,pm;
    P=(Polynomial)malloc(sizeof(Node));
    P->next=NULL;
    for(int i=n;i>0;i--)
    {
    	int coef,expn;
    	pn=(Polynomial)malloc(sizeof(Node));
    	pm=(Polynomial)malloc(sizeof(Node));
    	pn->next=pm;
    	std::cin>>coef>>expn;
    	if(coef)
		{
		pm->coef=coef;
		pm->expn=expn;
		pm->next=NULL;
		AddPolyn(P,pn);
    	/*pn->next=P->next;
    	P->next=pn;*/
		}
	}
	//MergePolyn(P);
	//SortPolyn(P); 
}//CreatPolyn
Polynomial CreatePolyn(int n)
{
	Polynomial pn,pm;
    Polynomial P;
	P=(Polynomial)malloc(sizeof(Node));
    P->next=NULL;
    for(int i=n;i>0;i--)
    {
    	int coef,expn;
    	pn=(Polynomial)malloc(sizeof(Node));
    	pm=(Polynomial)malloc(sizeof(Node));
    	pn->next=pm;
    	std::cin>>coef>>expn;
    	if(coef)
		{
		pm->coef=coef;
		pm->expn=expn;
		pm->next=NULL;
		AddPolyn(P,pn);
    	/*pn->next=P->next;
    	P->next=pn;*/
		}
	}
	MergePolyn(P);
	SortPolyn(P);
	return P;
}//TBD
int PolynLength(Polynomial &P)
{
	int len=0;
	Polynomial pl=P;
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return 0;}
	while(pl)
	{
		len++;
		pl=pl->next;
	}
	return len-1;
}//PolynLength
void PrintPolyn(Polynomial &P)
{	
	if(P==NULL) {std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	Polynomial pp=P->next;
	std::cout<<"f(x)=";
	while(pp)
	{
		if(pp->coef)std::cout<<pp->coef;
		if(pp->expn)std::cout<<"x^"<<pp->expn;
		pp=pp->next;
		if(pp)
		{
			if(pp->coef>0)std::cout<<"+";
		}
	}
	std::cout<<std::endl; 
}//PrintPolyn
void AddPolyn(Polynomial &A,Polynomial &B)//Need Correction(Done)
{
	if(A==NULL||B==NULL){std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	Polynomial Ha=A;
	Polynomial Hb=B;
	Polynomial Pa=A->next;
	Polynomial Pb=B->next; 
	Polynomial Pt;
	while(Pa&&Pb)
	{
		int ea,eb;
		ea=Pa->expn;
		eb=Pb->expn;
		if(ea<eb)
		{
			Ha=Pa;
			Pa=Pa->next;
		}
		else if(ea==eb)
		{
			int sum=Pa->coef+Pb->coef;
			if(sum!=0)
			{
				Pa->coef=sum;
				Ha=Pa;
				DeletePolyn(Hb,Pb);	
				Pb=Pb->next;
			}
			else
			{
				if(Pa->next==NULL)
				{	
					Ha->next=NULL;
					DeletePolyn(Hb,Pb);
					Pb=Pb->next;
					break;
				}
				else
				{
					Ha->next=Pa->next;
				}
				Pa=Pa->next;
				DeletePolyn(Hb,Pb);
				Pb=Pb->next;
			}
		}
		else if(ea>eb)
		{
			DeletePolyn(Hb,Pb);
			Ha->next=Pb;
			Pt=Pb->next;
			Pb->next=Pa;
			Pb=Pt;
		}
	}
	if(PolynLength(Hb)>0)
	{
		Pa=Ha;
		while(Pa->next)
		{
			Pa=Pa->next;
		}
		Pa->next=Hb->next;
	}
	free(Hb);
	Hb=NULL;
	B=Hb;
	return;
}
void SubtractPolyn(Polynomial &A,Polynomial &B)
{
	if(A==NULL||B==NULL){std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	Polynomial Pb=B->next;
	while(Pb)
	{
		Pb->coef=-Pb->coef;
		Pb=Pb->next;
	}
	AddPolyn(A,B);
	return;
}
void MultiplyPolyn(Polynomial &A,Polynomial &B)
{
	if(A==NULL||B==NULL){std::cout<<"ERROR00:Polynomial dosen't exist."<<std::endl; return;}
	Polynomial Pa=A->next;
	Polynomial Pb=B->next;
	Polynomial C=(Polynomial)malloc(sizeof(Node));
	C->next=NULL;
	while(Pb)
	{
		Polynomial D=(Polynomial)malloc(sizeof(Node));
		D->next=NULL;
		Pa=A->next;
    	while(Pa)
    	{
    		int coef,expn;
    		Polynomial pn;
    		pn=(Polynomial)malloc(sizeof(Node));
    		coef=Pa->coef*Pb->coef;
			expn=Pa->expn+Pb->expn; 
    		if(coef)
			{
				pn->coef=coef;
				pn->expn=expn;
    			pn->next=D->next;
    			D->next=pn;
			}
			Pa=Pa->next;
		}
		PrintPolyn(D);
		AddPolyn(C,D);
		PrintPolyn(C);
		Pb=Pb->next;
	}
	PrintPolyn(C);
	MergePolyn(C);
	SortPolyn(C);
	A=C;
	DestroyPolyn(B);
	return; 
}
int main()
{
	int n=0;
	int m;
	Polynomial A;
	Polynomial B;
	std::cin>>n>>m;
	CreatePolyn(A,n);
	B=CreatePolyn(m);
	PrintPolyn(A);
	PrintPolyn(B);
	//std::cout<<std::endl;
	/*std::cout<<PolynLength(A)<<std::endl;
	DestroyPolyn(A);
	std::cout<<PolynLength(A)<<std::endl;
	DestroyPolyn(A);*/
	//AddPolyn(A,B);
	MultiplyPolyn(A,B);
	//std::cout<<std::endl;
	//SwapPolyn(A,LocatePolyn(A,1),LocatePolyn(A,2));
	PrintPolyn(A);
	PrintPolyn(B);
    return 0;
}
