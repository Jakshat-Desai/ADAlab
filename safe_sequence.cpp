#include<iostream>
#include<vector>
using namespace std;
typedef vector<vector<int> > vvi;
typedef vector<bool> vb;
typedef vector<int> vi;

int num_processes;
int num_resources;
int num_safe_sequences=0;

void safeState(vvi need, vi available, vvi allocated, vi ans, vb completed)
{
    if(ans==num_processes)
    {
        for(int j=0;j<num_processes;j++)
            cout<<ans[j]<<" ";
        cout<<endl;
        num_safe_sequences++;
        return;
    }
    for(int i=0;i<num_processes;i++)
    {
        if(!completed[i])
        {
            bool r=1;
            for(int j=0;j<num_resources;j++)
                r=r&&(available[j]>=need[i][j]);
            if(r)
            {
                ans.push_back(i);
                for(int j=0;j<num_resources;j++)
                    available[j]+=allocated[i][j];
                completed[i]=true;
                safeState(need,available,allocated,ans,completed);
                ans.pop_back();
                completed[i]=false;
                for(int j=0;j<num_resources;j++)
                    available[j]-=allocated[i][j];
            }
        }
    }
}

int main()
{
    cout<<"Enter the number of processes: "; cin>>num_processes;
    cout<<"Enter the number of resources: "; cin>>num_resources;
    vvi allocated(num_processes,vector<int>(num_resources));
    vvi maximum(num_processes,vector<int>(num_resources));
    vvi need(num_processes,vector<int>(num_resources));
    vi available(num_resources);
    cout<<"Enter the Allocation matrix:\n";
    for(int i=0;i<num_processes;i++)
        for(int j=0;j<num_resources;j++)
            cin>>allocated[i][j];
    cout<<"Enter the Maximum need matrix:\n";
    for(int i=0;i<num_processes;i++)
        for(int j=0;j<num_resources;j++)
            cin>>maximum[i][j];
    cout<<"Enter the available vector:\n";
    for(int i=0;i<num_resources;i++)
        cin>>available[i];
    //computing need matrix
    for(int i=0;i<num_processes;i++)
        for(int j=0;j<num_resources;j++)
            need[i][j]=maximum[i][j]-allocated[i][j];
    vb completed(num_processes,0);
    vi ans;
    safeState(need,available,allocated,ans,completed);
    cout<<num_safe_sequences<<"\n";
}
/*
5 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
3 3 2
*/
/*
4 4
4 2 6 5
3 1 0 1
4 2 5 0
1 0 0 2
7 6 7 7
6 5 3 4
7 6 6 2
9 2 3 2
3 4 1 2
*/
