#include<bits/stdc++.h>
using namespace std;

vector<int> computePrefix(string p)
{
    vector<int> prefix(p.length(),0);
    int i=1,j=0;
    while(i<p.length())
    {
        if(p[i]==p[j])
        {
            prefix[i]=j+1;
            j++;
            i++;
        }
        else
        {
            if(j==0)i++;
            else j=prefix[j-1];
        }
    }
    return prefix;
}

vector<vector<int> > computeTransition(string p, int d=26)
{
    vector<int> prefix=computePrefix(p);
    vector<vector<int > > delta(p.length()+1,vector<int>(d,0));
    delta[0][p[0]-'a']=1;
    for(int i=1;i<=p.length();i++)
        for(int j=0;j<d;j++)
        {
            if(p[i]-'a'==j)
                delta[i][j]=i+1;
            else
                delta[i][j]=delta[prefix[i-1]][j];
        }
    return delta;
}

void match(string p, string t, int d=26)
{
    vector<vector<int> > delta=computeTransition(p,d);
    int q=0;
    for(int i=0;i<t.length();i++)
    {
        q=delta[q][t[i]-'a'];
        if(q==p.length())
            cout<<"Match occurs with shift: "<<i-q+1<<"\n";
    }
}

int main()
{
    string t,p;
    cout<<"Enter text: "; cin>>t;
    cout<<"Enter pattern: "; cin>>p;
    match(p,t);
}
