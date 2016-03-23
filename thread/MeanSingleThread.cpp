#include<iostream>
#include<vector>
#include<chrono>
using namespace std;

class mean{
  vector<vector<int>> data;
  chrono::steady_clock::time_point last_time;
  int last_index;
  int N;
  int sum ;
  int count;
  
  void move(){
    chrono::seconds gap =chrono::duration_cast<chrono::seconds>(
                   chrono::steady_clock::now()-last_time);
    for(int i = 0; i < gap.count(); i++){
      last_index = (last_index + 1) % N;
      sum -= data[last_index][0];
      count -= data[last_index][1];
      data[last_index][0] = 0;
      data[last_index][1] = 0;
    }
    last_time = chrono::steady_clock::now();
  }
  public:
    mean(int t):N(t), data(t,vector<int>(2,0)),
               sum(0), last_index(0), count(0){
       last_time = chrono::steady_clock::now();
    }

    void add(int x){
      move();
      data[last_index][0] += x;
      data[last_index][1] += 1;
      sum += x;
      count++;
    }

    float getMean(){
      move();
      if(count == 0) return 0;
      else return (float)sum / (float)count;
    } 
    
    int getCount(){
      return count;
    } 
};


int main(){
  mean test(10);
  bool run = true;
  while(run){
    cout<<endl<<"Input data : ";
    int temp = 0;
    cin >> temp;
    test.add(temp);
    cout<<endl<<"Mean: "<<test.getMean()
        <<" Number of data: "<<test.getCount();
    cout<<endl<<"Continue ? n for no : ";
    char n = 0;
    cin >> n;
    if(n == 'n') run = false;
  } 
}


