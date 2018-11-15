#include<bits/stdc++.h>
using namespace std;

int main(){
  int n,q, total_burst=0; cin>>n>>q;
  multimap<int,int> process;
  for(int i=0;i<n;++i){
    int arr, burst; cin>>arr>>burst;
    process.insert(make_pair(arr,burst));
    total_burst+=burst;
  }

  int cur=0, wait=0;
  while(!process.empty()){
    for(auto it=process.begin();it!=process.end();){
      int pr=min(q, it->second);
      cur+=pr; it->second-=pr;
      if(it->second<=0){
        wait+=cur-it->first;
        it=process.erase(it);
      }
      else ++it;
    }
  }
  wait-=total_burst;
  printf("Waiting time is: %0.4f\n", (wait*1.0)/n);
}