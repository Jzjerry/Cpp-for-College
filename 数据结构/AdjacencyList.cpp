#include<iostream>
#include<exception>
#include<queue>
#include<algorithm>
#include<vector>

#define MAX_VERTEX_NUM 20
#define min(a,b) (a)<(b)?(a):(b)

enum KIND_TAG{UNDIG,DIG};
 

class Arc
{
	public:
		int vex1,vex2;
		int info;
		Arc(int v1,int v2,int w):vex1(v1),vex2(v2),info(w){}
};

int cmp(const void* a,const void* b)
{
	Arc* ap=(Arc*)a;
	Arc* bp=(Arc*)b;
	return ap->info-bp->info;
} 

class ArcNode
{
    public:
        int adjvex;
        ArcNode *nextarc=NULL;
        int info;
        ArcNode(int vex):adjvex(vex){}
        ArcNode(int vex,ArcNode* arc,int d):adjvex(vex),nextarc(arc),info(d){}
};

class VNode
{
    public:
        int data=0;
        ArcNode* firstarc=NULL;
};

class ALGraph
{
    public:
        VNode* AdjList;
        std::vector<Arc> Arcs;
        int vexnum,arcnum=0;
        int kind;
        bool* visit;
        ALGraph(int KindTag,int vn)
        :kind(KindTag),vexnum(vn)
        {
            if(vn>MAX_VERTEX_NUM) throw"Too Much Vertexs";
            else
            {
                AdjList=new VNode[vexnum+1];
                visit=new bool[vexnum+1];
            }
			for(int i=1;i<=vexnum;i++)
			{
				visit[i]=true;
			}
        }
        void InsertArc(int Vex1,int Vex2,int weight)
        {
        	Arc a(Vex1,Vex2,weight);
        	Arcs.insert(Arcs.begin(),a);
            //Digraph Arc
            if(kind==DIG)
            {
                ArcNode* ptr=AdjList[Vex1].firstarc;
                AdjList[Vex1].firstarc=new ArcNode(Vex2,ptr,weight);
            }
            //Undigraph Arc
            else if(kind==UNDIG)
            {
                ArcNode* ptr1=AdjList[Vex1].firstarc;
                ArcNode* ptr2=AdjList[Vex2].firstarc;
                AdjList[Vex1].firstarc=new ArcNode(Vex2,ptr1,weight);
                AdjList[Vex2].firstarc=new ArcNode(Vex1,ptr2,weight);
            }
            arcnum++;
            return;
        }
        void PrintGraph()
        {
            for(int i=1;i<=vexnum;i++)
            {
                ArcNode* ptr=AdjList[i].firstarc;
                std::cout<<"From Vexter No."<<i<<":\n";
                while(ptr!=NULL)
                {
                    std::cout<<"{To Vexter No."<<ptr->adjvex<<" Weight:"<<ptr->info<<"}\n";
                    ptr=ptr->nextarc;
                }
                std::cout<<"End\n";
            }
            return;
        }
        void DFS_Graph(int Vex)
        {	
        	if(visit[Vex])
        	{
        		ArcNode* ptr=AdjList[Vex].firstarc;
        		visit[Vex]=false;
				std::cout<<"Vexter No."<<Vex<<" has been visited.\n";
        		while(ptr!=NULL)
        		{
        			DFS_Graph(ptr->adjvex);
        			ptr=ptr->nextarc;
				}
				return;
			}
			return;
		}
		void BFS_Graph(int Vex)
        {	
        	std::queue<int> Q;
        	for(int i=1;i<=vexnum;i++)
        	{
        		if(visit[Vex])
        		{
        			visit[Vex]=false;
        			std::cout<<"Vexter No."<<Vex<<" has been visited.\n";
        			Q.push(Vex);
        			while(!Q.empty())
        			{
        				int u=Q.front();
        				Q.pop();
        				for(ArcNode* w=AdjList[u].firstarc;w!=NULL;w=w->nextarc)
        				{
        					if(visit[w->adjvex])
        					{
        						visit[w->adjvex]=false;
        						std::cout<<"Vexter No."<<w->adjvex<<" has been visited.\n";
        						Q.push(w->adjvex);
							}
						}
					}
				}
			}
			return;
		}
        void Prim_MST(int startvex);
        void Kruskal_MST();
    protected:
        int _GetArc(int vex1,int vex2)
        {
        	if(vex1==vex2)
        	{
        		return 0;
			}
            ArcNode* PTR=AdjList[vex1].firstarc;
            while(PTR!=NULL)
            {
                if(PTR->adjvex==vex2)
                {
                    return PTR->info;
                }
                else
                {
                    PTR=PTR->nextarc;
                }
            }
            return 114514;//Unconnected
        }
};


int main()
{
    ALGraph P1(UNDIG,6);
    //ALGraph P2(UNDIG,5);
    P1.InsertArc(1,2,6);
    P1.InsertArc(1,4,5);
    P1.InsertArc(1,3,1);
    P1.InsertArc(3,4,5);
    P1.InsertArc(3,2,5);
    P1.InsertArc(3,5,6);
    P1.InsertArc(3,6,4);
    P1.InsertArc(2,5,3);
    P1.InsertArc(4,6,2);
    P1.InsertArc(5,6,6);
    P1.PrintGraph();
    P1.Kruskal_MST();
    return 0;
}
void ALGraph::Prim_MST(int startvex)
{
    //TO DO
    int closeedge[vexnum+1][2];//[0]--adjvex,[1]--lowcost
    for(int i=1;i<=vexnum;i++)
    {
        closeedge[i][0]=startvex;
        closeedge[i][1]=_GetArc(startvex,i);
    }
    for(int i=1;i<vexnum;i++)
    {
        int kmin=startvex;
        int closeedgemin=114514;
        for(int k=1;k<=vexnum;k++)
        {
            if(closeedge[k][1]!=0)
            {
                if(closeedgemin>closeedge[k][1])
                {
                    closeedgemin=closeedge[k][1];
                    kmin=k;
                }
            }
        }
        std::cout<<"MST_Arc: "<<closeedge[kmin][0]<<" to "<<kmin<<" cost: "<<closeedge[kmin][1]<<"\n";
        closeedge[kmin][1]=0;
        for(int j=1;j<=vexnum;j++)
        {
            int w=_GetArc(kmin,j);
            if(w<closeedge[j][1])
            {
                closeedge[j][0]=kmin;
                closeedge[j][1]=w;
            }
        }
    }
}

void ALGraph::Kruskal_MST()
{
	int tag[vexnum+1];
	for(int j=1;j<=vexnum;j++)
	{
		tag[j]=j;
	}
	qsort(&Arcs[0],Arcs.size(),sizeof(Arc),cmp);
	for(int i=0;i<arcnum;i++)
	{
		if(tag[Arcs[i].vex1]!=tag[Arcs[i].vex2])//此处可以并查集优化 
		{
			int pretag=tag[Arcs[i].vex1];
			for(int k=1;k<=vexnum;k++)
			{
				if(tag[k]==pretag)
				{
					tag[k]=tag[Arcs[i].vex2];
				}
			}
			std::cout<<"MST_Arc: "<<Arcs[i].vex1<<" to "<<Arcs[i].vex2<<" cost: "<<Arcs[i].info<<"\n";
		}
	}
	return ;
}
