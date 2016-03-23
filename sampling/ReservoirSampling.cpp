#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

vector<int>  ReservoirSampling(vector<int> & data, int k){
  if(k >= data.size()) return data;
  srand(time(NULL));
  vector<int> Reservoir(data.begin(), data.begin() + k);
  for(int i = k; i < data.size(); i++){
    int index = rand()%(i+1);
    if(index < k) Reservoir[index] = data[i]; 
  }
  return Reservoir;
}

int main(){
  srand(time(NULL));
  vector<int> data(1000, 0);
  for(int i = 0; i < 1000; i++)
    data[i] = rand()%1000;
  int k = rand()%10;
  vector<int> Reservoir = ReservoirSampling(data,k); 
  
  cout<<"First k elements in data: ";
  for(int i = 0; i < k; i++){
    cout<<data[i]<<" ";
  }
  cout<<endl<<"Reservoir Sampling Result: ";
  for(int i = 0; i < k; i++){
    cout<<Reservoir[i]<<" ";
  }
  cout<<endl;
  return 0;
}
