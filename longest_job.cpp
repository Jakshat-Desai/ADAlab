#include<bits/stdc++.h>
using namespace std;

int main(){
  int n; cin>>n;
  map<int,int> process;
  for(int i=0;i<n;++i){
    int arr_time, burst_time;
    cin>>arr_time>>burst_time;
    process[arr_time]=burst_time;
  }
  int cur=0, wait=0;
  while(!process.empty()){
    auto it=process.upper_bound(cur);
    if(it==process.begin()) {++cur; continue;}
    int big=-1;  //for maximum burst time for process arrived earlier than `cur`
    map<int,int>::iterator idx; // for storing maximum time iterator as indicated by `big`
    for(auto itr=process.begin();itr!=it;++itr){
      if(itr->second> big) big=itr->second, idx=itr;
    }
    wait+=cur-idx->first;
    cur+=idx->second;
    process.erase(idx);
  }
  cout<<"Waiting time:"<<(wait*1.0)/n<<endl;
}
