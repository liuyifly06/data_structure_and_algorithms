#include <iostream>
#include <thread>
#include <ctime>
#include <ratio>
#include <chrono>
#include <mutex>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

mutex m;//door handle


class average{
  queue<pair<int, chrono::steady_clock::time_point> > data;
  long long int sum;
  chrono::seconds life;
  bool delete_thread_run;
  thread del;
  public:
    average(chrono::seconds d):life(d){
        sum = 0;
        delete_thread_run = true;
  	life = chrono::seconds(10);
        del = thread(&average::deleteOldData, this);
        if(del.joinable()) del.detach();
    }
    average(){
        sum = 0;
        delete_thread_run = true;
    	life = chrono::seconds(10);
        del = thread(&average::deleteOldData, this);
        if(del.joinable()) del.detach();
    }
    ~average(){
        delete_thread_run = false;
        del.~thread();
    }
  
    int getSize(){
      return data.size();
    }
    
    float getAverage(){
      return (float)sum/(float)data.size();
    }
    
   void push(int val){
     m.lock();
     chrono::steady_clock::time_point t  = chrono::steady_clock::now();
     data.push(make_pair(val, t));
     sum += val;
     m.unlock();
   }
   
   void deleteOldData(){
     while(delete_thread_run){
       while(data.size() == 0 && delete_thread_run)
         this_thread::yield();
       while(!data.empty()){
         if(chrono::steady_clock::now() - data.front().second  > life){
            m.lock();
            sum -= data.front().first;
            data.pop();
            cout<<"One element Deleted"<<endl;
            m.unlock();
         }else{
           this_thread::sleep_until(data.front().second + life);
         }
       }
     }
   }
};



int main()
{
  average test;
  bool run = true;
  while(run){
    int temp = 0;
    cout<<"Input Value "<<endl;
    cin >> temp;
    test.push(temp);
    cout<<"Average    data.size()"<<endl;
    cout<<test.getAverage()<<"            "<<test.getSize()<<endl;
    char select;
    cout<<"Continue ? (y)es / (n)o"<<endl;
    cin >> select;
    if(select == 'n') run = false;
  }
  return 0;
}
