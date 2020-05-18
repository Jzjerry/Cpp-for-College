#include<iostream>

template<class T>
class SNode
{
    private:
        T key;
    public:
        SNode* left;
        SNode* right;
        SNode(const T& data):key(data),left(nullptr),right(nullptr){}
        SNode():left(nullptr),right(nullptr){}
        inline T GetKey(){return key;}
};


template<class T> 
class SortTree
{
    private:
        SNode<T>* _root=NULL;
        size_t NodeNum = 0;
        void _PreOrderTraverse(SNode<T>* root)
        {
            if(root)
            {
                std::cout<<root->GetKey()<<" ";
                if(root->left) _PreOrderTraverse(root->left);
                if(root->right) _PreOrderTraverse(root->right);
            }
            else
            {
                return;
            }
        }
        void _InOrderTraverse(SNode<T>* root)
        {
            if(root)
            {
                if(root->left) _InOrderTraverse(root->left);
                std::cout<<root->GetKey()<<" ";
                if(root->right) _InOrderTraverse(root->right);
            }
            else
            {
                return;
            }
        }
        SNode<T>* _SearchTree(T key,SNode<T>* _S);
    public:
        void InsertNode(T data);
        void PreOrderTraverse(){_PreOrderTraverse(_root);return;}
        void InOrderTraverse(){_InOrderTraverse(_root);return;}
        bool SearchTree(T data)
		{
			SNode<T>* st = _SearchTree(data,_root);
			if(st != NULL)
			{
				std::cout<<"node found \n";
				return true;
			}
			else 
			{
				std::cout<<"can't find node\n";
				return false;
			}
		}
        SortTree(int n):NodeNum(n)
        {
            for(int i = 0;i < n;i++)
            {
                T data;
                std::cout<<"Input Node: ";
                std::cin>>data;
                InsertNode(data);
                std::cout<<"Now the Sort Tree in_order_seq is: ";
                InOrderTraverse();
                std::cout<<"\n";
            }
        }
};

int main()
{
    int n;
    std::cout<<"Enter number of Nodes:\n";
    std::cin>>n;
    SortTree<int> A(n);
    A.InOrderTraverse();
    std::cout<<std::endl;
    A.PreOrderTraverse();
    std::cout<<"\nEnter for searching :\n";
    int num;
	std::cin>>num;
	A.SearchTree(num);
    return 0;
}

template<class T>
void SortTree<T>::InsertNode(T data)
{
    SNode<T>* newnode = new SNode<T>(data);
    if(_root == NULL)
    {
        _root = newnode;
    }
    else
    {
        SNode<T>* ptr=_root;
        SNode<T>* temp;
        int chlid=-1;
        while(ptr != NULL)
        {
        	temp = ptr;
            if(ptr->GetKey()<=data)
            {
            	ptr = ptr->right;
            	chlid = 1;
            }
            else if(ptr->GetKey()>data)
            {
            	ptr = ptr->left;
            	chlid = 2;
            }
        }
        if(chlid == 1)
        {
        	temp->right = newnode;
		}
		else if(chlid == 2)
		{
			temp->left = newnode; 
		}
		else
		{
			return;
		}
    }
    return ;
}

template<class T>
SNode<T>* SortTree<T>::_SearchTree(T key,SNode<T>* _S)
{
	if(!_S)
	{
		return NULL;
	}
	else if(key == _S->GetKey()){return _S;}
	else if(key < _S->GetKey()){return _SearchTree(key,_S->left);}
	else {return _SearchTree(key,_S->right);}
}
