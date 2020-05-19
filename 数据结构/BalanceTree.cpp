#include<iostream>


#define LH +1    //Left Higher
#define EH 0    //Equally High
#define RH -1   //Right Higher

template<class T>
class BTNode
{
    public:
        T data;
        int BalanceFactor=0;
        BTNode* right;
        BTNode* left;
        BTNode():right(nullptr),left(nullptr){}
        BTNode(const T &d=T()):data(d),right(nullptr),left(nullptr){}
        BTNode(const T &d=T(),const int &b=EH):data(d),BalanceFactor(b),right(nullptr),left(nullptr){} 
}; 

template<class T>
class BalanceTree
{
    private:
        BTNode<T>* _root;
        void _PreOrderTraverse(BTNode<T>* root)
        {
            if(root)
            {
                std::cout<<root->data<<" ";
                if(root->left) _PreOrderTraverse(root->left);
                if(root->right) _PreOrderTraverse(root->right);
            }
            else
            {
                return;
            }
        }
        void _InOrderTraverse(BTNode<T>* root)
        {
            if(root)
            {
                if(root->left) _InOrderTraverse(root->left);
                std::cout<<root->data<<" ";
                if(root->right) _InOrderTraverse(root->right);
            }
            else
            {
                return;
            }
        }
    public:
    	void  InsertNode(const T& data);
    	BalanceTree():_root(nullptr){}
    	BalanceTree(const size_t n):_root(nullptr)
    	{
    		for(int i=1;i<=n;i++)
    		{
    			std::cout<<"Enter Node No."<<i<<"\n";
    			T e;
    			std::cin>>e;
    			InsertNode(e);
    			//PreOrderTraverse();
			}
			std::cout<<"Tree has been build\n";
		}
		void PreOrderTraverse(){_PreOrderTraverse(_root);return;}
        void InOrderTraverse(){_InOrderTraverse(_root);return;}
    protected:
        void _R_Rotate(BTNode<T>* &p);
        void _L_Rotate(BTNode<T>* &p);
        void _LeftBalance(BTNode<T>* &Tree);
        void _RightBalance(BTNode<T>* &Tree);
        bool _InsertAVL(BTNode<T>* &Tree,T data,bool &taller);
};

int main()
{
	int n;
	std::cin>>n;
	BalanceTree<int> T1(n);
	std::cout<<"The PreOrder Sequence is:\n";
	T1.PreOrderTraverse();
	std::cout<<"\n";
	std::cout<<"The InOrder Sequence is:\n";
	T1.InOrderTraverse();
	std::cout<<"\n";
    return 0;
}

template<class T>
void BalanceTree<T>::_R_Rotate(BTNode<T>* &p)
{
    BTNode<T>* lc=p->left;
    p->left = lc->right;
    lc->right = p;
    p = lc;
    std::cout<<"Right Rotated\n";
    return;
}

template<class T>
void BalanceTree<T>::_L_Rotate(BTNode<T>* &p)
{
    BTNode<T>* rc=p->right;
    p->right = rc->left;
    rc->left = p;
    p = rc;
    std::cout<<"Left Rotated\n";
    return;
}

template<class T>
void BalanceTree<T>::InsertNode(const T &data)
{
    bool taller = true;
    _InsertAVL(_root,data,taller);
    return;
}

template<class T>
bool BalanceTree<T>::_InsertAVL(BTNode<T>* &Tree,T data,bool &taller)
{
    if(!Tree)
    {
        Tree = new BTNode<T>(data,EH);
        taller = true;
    }
    else
    {
        if(data<=Tree->data)//Left Insert
        {
            if(!(_InsertAVL(Tree->left,data,taller))) return false;
            if(taller)
            {
                if(Tree->BalanceFactor==LH)//If Left subtree is 1 higher before insert in left
                {						   //Which means BF of this node become +2
                    _LeftBalance(Tree);
                    taller = false;
                }
                else if(Tree->BalanceFactor==EH)//If subtree is balance before insert in left
                {								//Which means BF of this node become +1
                    Tree->BalanceFactor = LH;
                    taller = true;
                }
                else if(Tree->BalanceFactor==RH)//If right subtree is 1 higher before insert in left
                {								//Which means BF of this node become 0
                    Tree->BalanceFactor = EH;
                    taller = false;
                }
            }
        }
        else            //Right Insert
        {
            if(!(_InsertAVL(Tree->right,data,taller))) return false;
            if(taller)
            {
                if(Tree->BalanceFactor==LH)//If left subtree is 1 higher before insert in right
                {						   //Which means BF of this node become 0 
                    Tree->BalanceFactor = EH;
                    taller = false;
                }
                else if(Tree->BalanceFactor==EH)//If subtree is balance before insert in right
                {								//Which means BF of this node become -1
                    Tree->BalanceFactor = RH;
                    taller = true;
                }
                else if(Tree->BalanceFactor==RH)//If right subtree is 1 higher before insert in right
                {								//Which means BF of this node become -2
                    _RightBalance(Tree);
                    taller = false;
                }
            }
        }
    }
    return true;
}

template<class T>
void BalanceTree<T>::_LeftBalance(BTNode<T>* &Tree)
{
    BTNode<T>* leftchild = Tree->left;
    int lcbf =leftchild->BalanceFactor;
    if(lcbf == LH)                      //Do Single R Rotate when left child has a higher left subtree
    {
        leftchild->BalanceFactor = EH;
        Tree->BalanceFactor = leftchild->BalanceFactor;
        _R_Rotate(Tree);
    }
    else if(lcbf == RH)                 //Do Double LR Rotate when left child has a higher right subtree
    {
        BTNode<T>* rightd = leftchild->right;
        if(rightd->BalanceFactor==LH)
        {
            Tree->BalanceFactor = RH;
            leftchild->BalanceFactor = EH;
        }
        else if(rightd->BalanceFactor==EH)
        {
            Tree->BalanceFactor = EH;
            leftchild->BalanceFactor = EH;
        }
        else if(rightd->BalanceFactor==RH)
        {
            Tree->BalanceFactor = EH;
            leftchild->BalanceFactor = LH;
        }
        _L_Rotate(Tree->left);			//Let the Left child's right subtree become a left subtree
        _R_Rotate(Tree);				//then do a Single R Rotate
    }
    return;
}


template<class T>
void BalanceTree<T>::_RightBalance(BTNode<T>* &Tree)//Symmertry Process of _LeftBalance
{
    BTNode<T>* rightchild = Tree->right;
    int rcbf =rightchild->BalanceFactor;
    if(rcbf == RH)                      //Single L Rotate
    {
        rightchild->BalanceFactor = EH;
        Tree->BalanceFactor = rightchild->BalanceFactor;
        _L_Rotate(Tree);
    }
    else if(rcbf == LH)                 //Double RL Rotate
    {
        BTNode<T>* leftd = rightchild->left;
        if(leftd->BalanceFactor==RH)
        {
            Tree->BalanceFactor = LH;
            rightchild->BalanceFactor = EH;
        }
        else if(leftd->BalanceFactor==EH)
        {
            Tree->BalanceFactor = EH;
            rightchild->BalanceFactor = EH;
        }
        else if(leftd->BalanceFactor==LH)
        {
            Tree->BalanceFactor = EH;
            rightchild->BalanceFactor = RH;
        }
        _R_Rotate(Tree->right);
        _L_Rotate(Tree);
    }
    return;
}
