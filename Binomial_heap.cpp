#include<bits/stdc++.h>
using namespace std;

struct Node
{
    Node* par;
    int key;
    int degree;
    Node* child;
    Node* sib;
};

Node* newNode(int val)
{
    Node* n;
    n=new Node();
    n->key=val;
    n->par=NULL;
    n->child=NULL;
    n->sib=NULL;
    n->degree=0;
    return n;
}

void link(Node* &y, Node* &z)
{
    y->par=z;
    y->sib=z->child;
    z->child=y;
    z->degree+=1;
}

void DFS(Node* root)
{
    if(root==NULL)return;
    cout<<root->key<<" ";
    Node* ch; ch=root->child;
    while(ch!=NULL)
    {
        DFS(ch);
        ch=ch->sib;
    }
}

class Bin_Heap
{
    public:

    Node* head;
    int deg;

    Bin_Heap()
    {
        deg=0;
        head=NULL;
    }

    Node* minimum()
    {
        Node* x; x=head;
        Node* a; a=x;
        int ans=INT_MAX;
        do
        {
            if(ans>x->key){ans=x->key;a=x;}
            x=x->sib;
        }while(x!=NULL);
        return a;
    }

    void mergeHeaps(Bin_Heap H)
    {
        Node* x; x=H.head;
        Node* y; y=head;
        Node* ans;
        if(x==NULL ^ y==NULL)
        {
            ans=(x==NULL)?y:x;
            head=ans;
            return;
        }
        if(x->degree<y->degree)
        {
            ans=x;
            x=x->sib;
        }
        else
        {
            ans=y;
            y=y->sib;
        }
        Node* cur; cur=ans;
        do
        {
            if(x!=NULL && y!=NULL)
            {
                if(x->degree<y->degree)
                {
                    cur->sib=x;
                    x=x->sib;
                }
                else
                {
                    cur->sib=y;
                    y=y->sib;
                }
            }
            else if(x!=NULL)
            {
                    cur->sib=x;
                    x=x->sib;
            }
            else if(y!=NULL)
            {
                    cur->sib=y;
                    y=y->sib;
            }
            else break;
            cur=cur->sib;
        }while(1);
        head=ans;
    }

    void unionheap(Bin_Heap H)
    {
       if(H.head==NULL)return;
       Bin_Heap::mergeHeaps(H);
       Node *x, *prev_x, *next_x;
       prev_x=NULL; x=head; next_x=x->sib;
       while(next_x!=NULL)
       {
            if(x->degree!=next_x->degree || (next_x->sib!=NULL && next_x->sib->degree==x->degree))
            {
                prev_x=x;
                x=next_x;
            }
            else if(x->key <= next_x->key)
            {
                x->sib=next_x->sib;
                link(next_x,x);
            }
            else
            {
                if(prev_x==NULL)head=next_x;
                else prev_x->sib=next_x;
                link(x,next_x);
                x=next_x;
            }
            next_x=x->sib;
       }
    }

    void insertion(int x)
    {
        Bin_Heap H; H.head=newNode(x);
        Bin_Heap::unionheap(H);
    }

    int extractMin()
    {
        Node* m; m=Bin_Heap::minimum();
        Node* x; x=head;
        if(x==m)head=head->sib;
        else
        {
            while(x->sib!=m)x=x->sib;
            x->sib=x->sib->sib;
        }
        Node *pre,*c,*next;
        c=m->child; pre=NULL;
        while(c!=NULL)
        {
            if(c!=NULL)next=c->sib;
            c->sib=pre;
            pre=c;
            c=next;
        }
        Bin_Heap H; H.head=pre;
        Bin_Heap::unionheap(H);
        return m->key;
    }

    void decreaseKey(Node* x, int val)
    {
        if(val>=x->key){cout<<"Invalid\n";return;}
        x->key=val;
        Node *y, *z; y=x; z=x->par;
        while(z!=NULL && y->key<z->key)
        {
            swap(z->key,y->key);
            y=z;
            z=y->par;
        }
    }

    void deletion(Node *x)
    {
        Bin_Heap::decreaseKey(x,INT_MIN);
        Bin_Heap::extractMin();
    }

    void printHeap()
    {
        Node* x; x=head;
        while(x!=NULL)
        {
            DFS(x);
            x=x->sib;
            cout<<"\n";
        }
    }
};

int main()
{
    Bin_Heap H;
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
