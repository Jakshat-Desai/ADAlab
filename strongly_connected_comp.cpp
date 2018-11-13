#include<bits/stdc++.h>
using namespace std;

vector<int> toposort;
vector<bool> visited;

void dfs(vector<vector<int> > graph, int i, bool flag=1)
{
    if(visited[i])return;
    visited[i]=true;
    for(int j=0;j<graph[i].size();j++)
            dfs(graph,graph[i][j],flag);
    if(flag)toposort.push_back(i);
    else cout<<i<<" ";
}

void topo_order(vector<vector<int> > graph, int n)
{
    for(int i=0;i<n;i++)dfs(graph,i);
    reverse(toposort.begin(),toposort.end());
}

int main()
{
    int n; // number of nodes
    int e; // number of edges
    cout<<"Enter the number of vertices:\n"; cin>>n;
    cout<<"Enter the number of edges:\n"; cin>>e;
    vector<vector<int> > graph(n); // adjacency list of the graph
    vector<vector<int> > tr_graph(n); // adjacency list of transpose graph
    visited.assign(n,false); //visited array
    for(int i=0;i<e;i++)
    {
        int st,ed; cout<<"Enter the start and end vertex of the edge:\n"; cin>>st>>ed;
        graph[st].push_back(ed);
        tr_graph[ed].push_back(st);
    }
    topo_order(graph,n);
    for(int i=0;i<n;i++)visited[i]=false;
    cout<<"Strongly connected components:\n";
    for(int i=0;i<n;i++)
    {
        if(!visited[toposort[i]])
        {
            dfs(tr_graph,toposort[i],false);
            cout<<"\n";
        }
    }
}
// 9 13 0 1 1 2 1 4 2 2 2 5 3 1 3 6 4 3 4 0 5 7 6 4 7 8 8 5
