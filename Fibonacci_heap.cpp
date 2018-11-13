#include<bits/stdc++.h>
using namespace std;

struct Node
{
    Node* par;
    Node* child;
    Node* right;
    Node* left;
    int key;
    int degree;
    bool marked;
};

Node* newNode(int val)
{
    Node* x; x=new Node();
    x->key=val;
    x->par=NULL;
    x->child=NULL;
    x->left=x;
    x->right=x;
    x->degree=0;
    x->marked=false;
    return x;
}

void print_Node(Node* x)
{
    cout<<x->key;
    cout<<"(par:"<<((x->par==NULL)?(-1):(x->par->key))<<",";
    cout<<"left:"<<x->left->key<<",";
    cout<<"right:"<<x->right->key<<",";
    cout<<"child:"<<((x->child==NULL)?-1:(x->child->key))<<",";
    cout<<"deg:"<<x->degree<<")\n";
}

void DFS(Node* x)
{
    if(x==NULL)return;
    print_Node(x);
    if(x->child==NULL)return;
    Node *per, *cur;
    per=x->child;
    cur=per;
    do
    {
        DFS(cur);
        cur=cur->right;
    }while(cur!=per);
}

Node* SRCH(Node* x, int val)
{
    if(x==NULL)return;
    if(x->key==val)return x;
    if(x->child==NULL)return;
    Node *per, *cur;
    per=x->child;
    cur=per;
    do
    {
        SRCH(cur,val);
        cur=cur->right;
    }while(cur!=per);
}

void Node_delete(Node* &x)
{
    if(x==NULL)return;
    Node *a,*b;
    a=x->left;
    b=x->right;
    a->right=b;
    b->left=a;
    x->left=x;
    x->right=x;
}

class Fib_Heap
{
    public:

    Node* minNode;
    int tree;
    int marked;
    int num;

    Fib_Heap()
    {
        minNode=NULL;
        tree=0;
        marked=0;
        num=0;
    }

    Node* minimum()
    {
        return minNode;
    }

    void concat(Fib_Heap H)
    {
        if(H.minNode==NULL || minNode==NULL)return;
        Node* y; y=H.minNode->left;
        Node* x; x=minNode->left;
        x->right=H.minNode;
        H.minNode->left=x;
        y->right=minNode;
        minNode->left=y;
    }

    void unionHeaps(Fib_Heap H)
    {
        if(H.minNode==NULL)return;
        Fib_Heap::concat(H);
        if(minNode==NULL)
        {
            minNode=H.minNode;
            return;
        }
        if(H.minNode->key<minNode->key)
            minNode=H.minNode;
        tree+=H.tree;
        marked+=H.marked;
        num+=H.num;
    }

    void insertion(int x)
    {
        Node* n; n=newNode(x);
        Fib_Heap H; H.minNode=n;
        Fib_Heap::unionHeaps(H);
        tree++;
        num++;
    }

    void insertion(Node* n)
    {
        if(n==NULL)return;
        n->left=n; n->right=n;
        n->par=NULL; n->marked=false;
        Fib_Heap H; H.minNode=n;
        Fib_Heap::unionHeaps(H);
        tree++;
    }

    void link(Node* &y, Node* &x)
    {
        Node_delete(y);
        if(x==y)return;
        if(x->child!=NULL)
        {
            Node* c; c=x->child;
            y->left=c->left;
            y->right=c;
            c->left=y;
            y->left->right=y;
        }
        x->child=y;
        x->degree++;
        y->par=x;
        if(y->marked)marked--;
        y->marked=false;
    }

    void consolidate()
    {
        if(minNode==NULL)return;
        Node* A[num];
        for(int i=0;i<num;i++)A[i]=NULL;
        Node* cur; cur=minNode;
        vector<Node*> nodes;
        do{
                nodes.push_back(cur);
                cur=cur->right;
        }while(cur!=minNode);
        for(int i=0;i<nodes.size();i++){
            Node*x; x=nodes[i];
            int d=x->degree;
            while(A[d]!=NULL && d<tree)
            {
                Node* y; y=A[d];
                if(x->key > y->key)swap(x,y);
                Fib_Heap::link(y,x);
                A[d++]=NULL;
            }
            A[d]=x;
        }
        Fib_Heap H;
        for(int i=0;i<num;i++)
            if(A[i]!=NULL)H.insertion(A[i]);
        minNode=H.minNode;
        tree=H.tree;
    }

    int extractMin()
    {
        if(minNode==NULL)return 34404;
        int val=minNode->key;
        num--;
        Node *c,*per; c=minNode->child; per=c;
        minNode->child=NULL;
        minNode->degree=0;
        if(c!=NULL)
        do{
            c->par=NULL;
            Node* cur; cur=c;
            c=c->right;
            if(cur->marked)marked--;
            Fib_Heap::insertion(cur);
        }while(c!=per);
        Node* x; x=minNode->right;
        Node_delete(minNode);
        tree--;
        minNode=x;
        Fib_Heap::consolidate();
        return val;
    }

    void cut(Node* x, Node* y)
    {
        y->child=x->right;
        if(x->child==x)y->child=NULL;
        Node_delete(x);
        y->degree--;
        x->par=NULL;
        if(x->marked)marked--;
        x->marked=false;
        Fib_Heap::insertion(x);
    }

    void cascadingCut(Node* y)
    {
        Node* z; z=y->par;
        if(z!=NULL)
        {
            if(!(y->marked))y->marked=true;
            else
            {
                Fib_Heap::cut(y,z);
                Fib_Heap::cascadingCut(z);
            }
        }
    }

    void decreaseKey(Node* x, int k)
    {
        if(k>x->key)return;
        x->key=k;
        Node* y; y=x->par;
        if(y!=NULL && x->key<y->key)
        {
            Fib_Heap::cut(x,y);
            Fib_Heap::cascadingCut(y);
        }
        if(x->key<minNode->key)
            minNode=x;
    }

    void deletion(Node* x)
    {
        Fib_Heap::decreaseKey(x,INT_MIN);
        Fib_Heap::extractMin();
    }

    void printHeap()
    {
        if(minNode==NULL){cout<<"Heap is empty\n"; return;}
        cout<<"Fibonacci Heap:\n";
        Node *per,*cur;
        per=minNode;
        cur=per;
        do
        {
            DFS(cur);
            cout<<"\n";
            cur=cur->right;
        }while(cur!=per);
        cout<<"Tree count: "<<tree<<"\n";
    }

    Node* search_(int val)
    {
        if(minNode==NULL){cout<<"Heap is empty\n"; return;}
        Node *per,*cur;
        per=minNode;
        cur=per;
        do
        {
            SRCH(cur,val);
            cur=cur->right;
        }while(cur!=per);
    }
};

int main()
{
    Fib_Heap H;
    while(1)
    {
        int i; cout<<"Enter:\n1 to insert\n2 to Extract Min\n3 to delete\n4 to get minimum\nany other number to quit\n";
        cin>>i;
        if(i==1)
        {
            int x; cout<<"Enter the number to be inserted:\n"; cin>>x;
            H.insertion(x);
            H.printHeap();
        }
        else if(i==2)
        {
            cout<<"Min element: "<<H.extractMin()<<"\n";
            H.printHeap();
        }
        else if(i==3)
        {
            cout<<"Deleting min:\n"; H.deletion(H.minimum());
            H.printHeap();
        }
        else if(i==4)
        {
            Node* x; x=H.minimum();
            cout<<"Minimum: "<<x->key<<"\n";
        }
        else break;
        cout<<"\n";
    }
}
//1 3 1 9 1 6 1 5 1 8 1 7 1 1 1 2 1 10 2
