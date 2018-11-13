#include<bits/stdc++.h>
#define cd complex<double>
using namespace std;
double pi=acos(-1);
vector<cd> fft(vector<cd> poly, int inv)
{
    if(poly.size()==1)return poly;
    vector<cd> a0,a1;
    int n=poly.size();
    for(int i=0;i<n;i++)
    {
        if(i%2==0)a0.push_back(poly[i]);
        else a1.push_back(poly[i]);
    }
    double ang=(2.0*pi*inv)/n;
    cd w(1);
    cd wn(cos(ang),sin(ang));

    a0=fft(a0,inv);
    a1=fft(a1,inv);

    for(int i=0;i*2<n;i++)
    {
        cd t=w*a1[i];
        poly[i]=a0[i]+t;
        poly[i+n/2]=a0[i]-t;
        if(inv==-1){
            poly[i]/=2;
            poly[i+n/2]/=2;
        }
        w=w*wn;
    }
    return poly;
}

void product(vector<cd> poly1, vector<cd> poly2)
{
    int n=1;
    while(n<poly1.size()+poly2.size())
        n=n<<1;

    poly1.resize(n);
    poly2.resize(n);

    poly1=fft(poly1,1);
    poly2=fft(poly2,1);

    for(int i=0;i<n;i++)
        poly1[i]=poly1[i]*poly2[i];

    poly1=fft(poly1,-1);

    for(int i=0;i<poly1.size();i++)
        cout<<round(poly1[i].real())<<" ";
}

int main()
{
    int deg1,deg2,coeff;
    cout<<"Enter the degree of first polynomial:"; cin>>deg1;
    cout<<"Enter the degree of second polynomial:"; cin>>deg2;
    vector<cd> poly1(deg1+1);
    vector<cd> poly2(deg2+1);
    cout<<"Enter the coefficients of the first polynomial:\n";
    for(int i=0;i<=deg1;i++)
    {
        cin>>coeff;
        poly1[i]=cd(coeff);
    }
    cout<<"Enter the coefficients of the second polynomial:\n";
    for(int i=0;i<=deg2;i++)
    {
        cin>>coeff;
        poly2[i]=cd(coeff);
    }
    product(poly1,poly2);
}
