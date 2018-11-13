#include<bits/stdc++.h>
using namespace std;

bool checkEqual(string p, string t, int ind)
{
	for(int i=0;i<p.length();i++)
		if(p[i]!=t[i+ind])
            return false;
	return true;
}
void rabinkarp(string p, string t, int d=10, int q=27)
{
	int cost_pat=0;
	int cur_cost=0;
	int m=p.length();
	int n=t.length();
	if(n<m)return;
	int h=1;
	for(int i=0;i<m-1;i++)
		h=(h*d)%q;
	for(int i=0;i<m;i++)
	{
		cost_pat=(cost_pat*d+(p[i]-'a'+1))%q;
		cur_cost=(cur_cost*d+(t[i]-'a'+1))%q;
	}
	for(int i=0;i<=n-m;i++)
	{
		if(cur_cost==cost_pat)
			if(checkEqual(p,t,i))
				cout<<"Match with shift: "<<i<<"\n";
		if(i<n-m)
		{
			cur_cost=(d*(cur_cost-(t[i]-'a'+1)*h)+(t[i+m]-'a'+1))%q;
			if(cur_cost<0)cur_cost+=q;
		}
	}
}

int main()
{
    string p,t;
    cout<<"Enter string:\n"; cin>>t;
    cout<<"Enter pattern:\n"; cin>>p;
	int d,q;
	cout<<"Enter d and q:\n";
	cin>>d>>q;
	rabinkarp(p,t,d,q);
}
