#include<bits/stdc++.h>
using namespace std;

vector<vector<float> > L;
vector<vector<float> > U;

void decompose(vector<vector<float> > a)
{
    int n=a.size();
    for(int i=0;i<n;i++)
    {
        U[i][i]=a[i][i];
        L[i][i]=1;
        for(int j=i+1;j<n;j++)
        {
            L[j][i]=a[j][i]/a[i][i];
            U[i][j]=a[i][j];
        }
        for(int j=i+1;j<n;j++)
            for(int k=i+1;k<n;k++)
                a[j][k]=a[j][k]-L[j][i]*U[i][k];
    }
}

void solve(vector<float> &y, vector<float> b, vector<float> &x, int n)
{
    for(int i=0;i<n;i++)
    {
        float sum=0;
        for(int j=0;j<i;j++)
            sum=sum+L[i][j]*y[j];
        y[i]=b[i]-sum;
    }
    for(int i=n-1;i>=0;i--)
    {
        float sum=0;
        for(int j=i+1;j<n;j++)
            sum=sum+U[i][j]*x[j];
        x[i]=(y[i]-sum)/U[i][i];
    }
    cout<<"Solution vector:\n";
    for(int i=0;i<n;i++)
        cout<<"x"<<i<<"="<<x[i]<<"\n";
}

int main()
{
    cout<<"Enter the number of unknowns:"; int n; cin>>n;
    vector<float> y(n);
    vector<float> x(n);
    vector<float> b(n);
    vector<vector<float> > a(n,vector<float>(n));
    cout<<"Write the entries for the coefficient matrix:\n";
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>a[i][j];
    cout<<"Enter the constant vector:\n";
    for(int i=0;i<n;i++)cin>>b[i];
    L.assign(n,vector<float>(n));
    U.assign(n,vector<float>(n));
    decompose(a);
    cout<<"Lower:\n";
    for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)cout<<L[i][j]<<" ";
            cout<<"\n";
    }
    cout<<"Upper:\n";
    for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)cout<<U[i][j]<<" ";
            cout<<"\n";
    }
    solve(y,b,x,n);
}
