#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int main()
{
	int u,v,q,U[4],V[4],T[4];
	cin>>u>>v;
	U[1]=1;U[2]=0;U[3]=u;
	V[1]=0;V[2]=1;V[3]=v;
	while(V[3]!=0)
	{
		q=floor(float(U[3]/V[3]));
		T[1]=U[1]-q*V[1];
		T[2]=U[2]-q*V[2];
		T[3]=U[3]-q*V[3];
		U[1]=V[1];
		U[2]=V[2];
		U[3]=V[3];
		V[1]=T[1];
		V[2]=T[2];
		V[3]=T[3];
	}
	cout<<U[3]<<"\n";
}
