#include<iostream>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<vector>
using namespace std;

mutex mx;
condition_variable cv;
int buf;

void consumer(int id){
  unique_lock<mutex> lk(mx);
  while(!buf) cv.wait(lk);
  cout<<"C-Thread: "<<id<<endl;
  buf--;
  cv.notify_all();
}
void producer(int id){
  unique_lock<mutex> lk(mx);
  while(buf >= 5) cv.wait(lk);
  cout<<"P-Thread: "<<id<<endl;
  ++buf;
  cv.notify_all();
}
int main(){
  int ct=15;
  vector<thread> p(ct), c(ct);
  for(int i=0;i<ct;++i){
    c[i]=thread(consumer,i);
    p[i]=thread(producer,i);
  }
  cv.notify_all();
  for(int i=0;i<ct;++i){
    p[i].join();
    c[i].join();
  }
}