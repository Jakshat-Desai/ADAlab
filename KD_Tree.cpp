#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
struct Node{
    int v;
    int hv;
    vector<pii> a;
    Node *left;
    Node *right;
    Node(){
        v=0;
        hv=0;
        left=0;
        right=0;
    }
};
bool comp1(pii a,pii b){
    return a.first<b.first;
}
bool comp2(pii a,pii b){
    return a.second<b.second;
}
int median(vector<pii> &a,int hv){
    if(hv==0){
        sort(a.begin(),a.end(),comp1);
        return a[a.size()/2].first;
    }else{
        sort(a.begin(),a.end(),comp2);
        return a[a.size()/2].second;
    }
}
struct Node* build(vector<pii> p,int d){
    Node* z=new Node();
    vector<pii> l,r;
    if(p.size()==1){
        z->a=p;
        return z;
    }
    int m,i;
    if(d%2==0){
        m=median(p,0);
        if(p.size()==2){
            l.push_back(p[0]);
            r.push_back(p[1]);
        }else{
            for(i=0;i<p.size();i++){
                if(p[i].first < m)
                    l.push_back(p[i]);
                else
                    r.push_back(p[i]);
            }
        }
    }else{
        m=median(p,1);

        if(p.size()==2){
            l.push_back(p[0]);
            r.push_back(p[1]);
        }else{


            for(i=0;i<p.size();i++){
                if(p[i].second < m)
                    l.push_back(p[i]);
                else
                    r.push_back(p[i]);
            }
        }
    }
    cout<<endl;
    cout<<"Split "<<d%2<<" "<<m<<endl;
    cout<<"Left\n";
    for(auto i:l)
        cout<<"( "<<i.first<<" "<<i.second<<" ) ";
    cout<<endl;

    cout<<"Right\n";
    for(auto i:r)
        cout<<"( "<<i.first<<" "<<i.second<<" ) ";
    cout<<endl<<endl;
    z->v=m;
    z->hv=d%2;
    z->left=build(l,d+1);
    z->right=build(r,d+1);
    return z;
}

void bfs(Node *z){
    queue<Node*> q;
    q.push(z);
    while(!q.empty()){
        Node* t=q.front();
        q.pop();
        cout<<t->hv<<" "<<t->v<<endl;
        if(t->left)
            q.push(t->left);
        if(t->right)
            q.push(t->right);
    }
}

int main(){
    vector<pii> a={{1,1},{2,3},{3,1},{4,2},{5,5}};
    for(auto i:a)
        cout<<"( "<<i.first<<" "<<i.second<<" ) ";
    cout<<endl;
    Node *r=build(a,0);
    //bfs(r);
}
