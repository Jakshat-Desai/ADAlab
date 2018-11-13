#include<bits/stdc++.h>
using namespace std;

int assembly_line_shortest(int n, int &last, int min_tot_time_1[], int min_tot_time_2[], int prss_time_1[], int prss_time_2[], int switch_time_1[], int switch_time_2[], int enter1, int enter2, int exit1, int exit2, int parent1[], int parent2[])
{
    parent1[0]=1; parent2[0]=2;
    min_tot_time_1[0]=enter1+prss_time_1[0];
    min_tot_time_2[0]=enter2+prss_time_2[0];
    for(int i=0;i<n;i++)
    {
        if(min_tot_time_1[i]>=min_tot_time_2[i]+switch_time_2[i])
            {
                parent1[i+1]=2;
                min_tot_time_1[i+1]=min_tot_time_2[i]+switch_time_2[i];
            }
        else
            {
                parent1[i+1]=1;
                min_tot_time_1[i+1]=min_tot_time_1[i];
            }
        if(min_tot_time_2[i]>=min_tot_time_1[i]+switch_time_1[i])
            {
                parent2[i+1]=1;
                min_tot_time_2[i+1]=min_tot_time_1[i]+switch_time_1[i];
            }
        else
            {
                parent2[i+1]=2;
                min_tot_time_2[i+1]=min_tot_time_2[i];
            }
        min_tot_time_1[i+1]+=prss_time_1[i+1];
        min_tot_time_2[i+1]+=prss_time_2[i+1];
    }
    for(int i=0;i<n;i++)cout<<min_tot_time_1[i]<<" "; cout<<"\n";
    for(int i=0;i<n;i++)cout<<min_tot_time_2[i]<<" "; cout<<"\n";
    if(min_tot_time_1[n-1]+exit1>=min_tot_time_2[n-1]+exit2)
    {
        last=2;
        return min_tot_time_2[n-1]+exit2;
    }
    else
    {
        last=1;
        return min_tot_time_1[n-1]+exit1;
    }
}

void path_traversed(int last, int parent1[], int parent2[], int n)
{
    if(n==0)return;
    int l=(last==1)?parent1[n-1]:parent2[n-1];
    path_traversed(l,parent1,parent2,n-1);
    cout<<"->"<<n<<"("<<last<<")";
}

int main()
{
    int n; //number of stations
    int prss_time_1[10000]; //processing times of line 1
    int prss_time_2[10000]; //processing time of line 2
    int switch_time_1[10000]; //switching times of line 1
    int switch_time_2[10000]; //switching times of line 2
    int enter1,enter2; //entry times for lines 1 and 2
    int exit1,exit2; //exit times for lines 1 and 2
    int parent1[10000],parent2[10000]; //parent arrays for the parent station of each station for line 1 and line 2 respectively
    int min_tot_time_1[10000], min_tot_time_2[10000]; //min time required to reach ith station
    int last; //line number at which assembly ends
    cout<<"Enter the number of stations:\n"; cin>>n;
    cout<<"Enter the processing times of stations in line 1:\n"; for(int i=0;i<n;i++)cin>>prss_time_1[i];
    cout<<"Enter the processing times of stations in line 2:\n"; for(int i=0;i<n;i++)cin>>prss_time_2[i];
    cout<<"Enter the switching times of stations in line 1:\n"; for(int i=0;i<n-1;i++)cin>>switch_time_1[i];
    cout<<"Enter the switching times of stations in line 2:\n"; for(int i=0;i<n-1;i++)cin>>switch_time_2[i];
    cout<<"Enter the entering times for lines 1 and 2:\n"; cin>>enter1>>enter2;
    cout<<"Enter the exit times for lines 1 and 2:\n"; cin>>exit1>>exit2;
    cout<<"Minimum time taken to traverse the assembly line is:\n"<<assembly_line_shortest(n,last,min_tot_time_1,min_tot_time_2,prss_time_1,prss_time_2,switch_time_1,switch_time_2,enter1,enter2,exit1,exit2,parent1,parent2)<<"\n";
    cout<<"Path traversed:\n"; path_traversed(last,parent1,parent2,n); cout<<"\n";
}
//6 7 9 3 4 8 4 8 5 6 4 5 7 2 3 1 3 4 2 1 2 3 1 2 4 3 2
//4 4 5 3 2 2 10 1 4 7 4 5 9 2 8 10 12 18 7
