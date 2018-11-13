#include<bits/stdc++.h>
using namespace std;

int mod_exp(int a, int n, int b)
{
    int ans=1;
    int z=a%b;
    while(n>0)
    {
        if(n&1)
        {
            ans=(ans*z)%b;
        }
        z=(z*z)%b;
        n=n>>1;
    }
    return ans;
}

int main()
{
    cout<<"Enter a:"; int a; cin>>a;
    cout<<"Enter n:"; int n; cin>>n;
    cout<<"Enter b:"; int b; cin>>b;
    cout<<"(a^n)%b="<<mod_exp(a,b,n)<<"\n";
}
