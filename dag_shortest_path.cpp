#include<bits/stdc++.h>
using namespace std;

vector<int> toposort;
vector<bool> visited;

void dfs(vector<vector<pair<int,int > > > graph, int i, bool flag=1)
{
    if(visited[i])return;
    visited[i]=true;
    for(int j=0;j<graph[i].size();j++)
            dfs(graph,graph[i][j].first,flag);
    if(flag)toposort.push_back(i);
    else cout<<i<<" ";
}

void topo_order(vector<vector<pair<int,int > > > graph, int n)
{
    for(int i=0;i<n;i++)dfs(graph,i);
    reverse(toposort.begin(),toposort.end());
}

void get_path(vector<int> par, vector<int> dis, int i, int src)
{
    cout<<"Minimum distance between "<<src<<" and "<<i<<" is "<<dis[i]<<"\n";
    cout<<"\tPath: ";
    stack<int> s;
    while(i!=par[i])
    {
        s.push(i);
        i=par[i];
    }
    cout<<0;
    while(!s.empty())
    {
        cout<<"->"<<s.top();
        s.pop();
    }
    cout<<"\n";
}

void DAG_shortest(vector<vector<pair<int,int > > > graph, vector<int> &par, vector<int> &dis, int src, int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<graph[toposort[i]].size();j++)
            if(dis[graph[toposort[i]][j].first]>dis[toposort[i]]+graph[toposort[i]][j].second)
            {
                dis[graph[toposort[i]][j].first]=dis[toposort[i]]+graph[toposort[i]][j].second;
                par[graph[toposort[i]][j].first]=toposort[i];
            }
    for(int i=0;i<n;i++)get_path(par,dis,i,src);
}
int main()
{
    int n; // number of nodes
    int e; // number of edges
    int src; //source vertex
    cout<<"Enter the number of vertices:\n"; cin>>n;
    cout<<"Enter the number of edges:\n"; cin>>e;
    vector<vector<pair<int,int> > > graph(n); // adjacency list of the graph
    vector<int> dis(n,9999999); // shortest distances of vertices from source
    vector<int> par(n); for(int i=0;i<n;i++)par[i]=i; // par[i] stores the parent vertex of vertex i
    visited.assign(n,false); //visited array
    for(int i=0;i<e;i++)
    {
        int st,ed,d; cout<<"Enter the start and end vertex and length of the edge:\n"; cin>>st>>ed>>d;
        graph[st].push_back({ed,d});
    }
    cout<<"Enter the source vertex:\n"; cin>>src;
    dis[src]=0;
    topo_order(graph,n);
    cout<<"\n";
    DAG_shortest(graph,par,dis,src,n);
}
//5 8 0 1 7 0 2 5 1 2 1 1 3 6 1 4 6 2 3 1 2 4 6 3 4 3 0
