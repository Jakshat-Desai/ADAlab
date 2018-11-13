#include<bits/stdc++.h>
using namespace std;

vector<int> djikstra(vector<vector<pair<int,int > > > graph, int s)
{
	int n=graph.size();
	vector<int> dist(n,1e8);
	set<pair<int,int > > st;
	st.insert({0,s});
	dist[s]=0;
	while(!st.empty())
	{
		int d=st.begin()->first;
		int v=st.begin()->second;
		for(int i=0;i<graph[v].size();i++)
			if(dist[graph[v][i].first]>dist[v]+graph[v][i].second)
			{
				dist[graph[v][i].first]=dist[v]+graph[v][i].second;
				st.insert({dist[graph[v][i].first],graph[v][i].first});
			}
		st.erase(st.begin());
	}
	return dist;
}

vector<int> BellmanFord(vector<vector<pair<int,int > > > graph, int s)
{
	int n=graph.size();
	vector<int> dist(n,1e8);
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<graph[i].size();j++)
				if(dist[graph[i][j].first]>dist[i]+graph[i][j].second)
					dist[graph[i][j].first]=dist[i]+graph[i][j].second;
	return dist;
}

int main()
{
	cout<<"Enter the number of nodes:\n"; int n; cin>>n;
	cout<<"Enter the number of edges:\n"; int m; cin>>m;
	vector<vector<pair<int,int > > > graph(n+1);
	vector<vector<pair<int,int > > > graph_djikstra(n+1);
	vector<vector<int > > ans;
	for(int i=1;i<=n;i++)
		graph[0].push_back({i,0});
	for(int i=0;i<m;i++)
	{
		int u,v,w;
		cout<<"Enter start, end and edge weight\n";
		cin>>u>>v>>w;
		graph[u].push_back({v,w});
	}
	vector<int> h=BellmanFord(graph,0);
	graph_djikstra=graph;
	for(int i=0;i<=n;i++)
		for(int j=0;j<graph[i].size();j++)
			graph_djikstra[i][j].second+=h[i]-h[graph_djikstra[i][j].first];
	for(int i=1;i<=n;i++)
		ans.push_back(djikstra(graph,i));
	for(int i=1;i<ans.size();i++)
		for(int j=0;j<ans[i].size();j++)
			ans[i][j]-=h[i]-h[j];
	cout<<"Distance Vector:\n";
	for(int i=0;i<ans.size();i++)
	{
		for(int j=1;j<ans[i].size();j++)
			cout<<ans[i][j]<<" ";
		cout<<"\n";
	}
}
