#include<bits/stdc++.h>
using namespace std;

vector<int> computePrefix(string p)
{
    int i=1,j=0;
    vector<int> prefix(p.length(),0);
    while(i<p.length())
    {
        if(p[i]==p[j])
        {
            prefix[i]=j+1;
            i++;
            j++;
        }
        else
        {
            if(j==0)
            {
                prefix[i]=0;
                i++;
            }
            else
            {
                j=prefix[j-1];
            }
        }
    }
    return prefix;
}

void kmp(string p, string t)
{
    vector<int> prefix=computePrefix(p);
    int i=0,j=0;
    while(i<t.length())
    {
        if(t[i]==p[j] && j<p.length())
        {
            i++;
            j++;
        }
        else
        {
            if(j==p.length())
            {
                cout<<"Match found with shift: "<<i-j<<"\n";
                i=i-j+1;
                j=0;
            }
            else
            {
                if(j==0)i++;
                else j=prefix[j-1];
            }
        }
    }
    if(j==p.length())
        cout<<"Match found with shift: "<<i-j<<"\n";
}

int main()
{
    string s,p;
    cout<<"Enter text:"; cin>>s;
    cout<<"Enter pattern:"; cin>>p;
    kmp(p,s);
}
