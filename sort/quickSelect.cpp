#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<chrono>
using namespace std;

void swap(vector<int> & nums, int i, int j){
  int temp = nums[i];
  nums[i] = nums[j];
  nums[j] = temp;
}

int partition(vector<int> & nums, int l, int r){
  int pivot = nums[r];
  int p = l-1;
  for(int i = l; i <= r; i++)
    if(nums[i] <= pivot)
      swap(nums, ++p, i);
  return p;
}

int quickSelect(vector<int> & nums, int k){
  int l = 0;
  int r = nums.size()-1;
  int p = nums.size();
  while(p != k-1){
    if(p < k-1){
      l = p+1;
      p = partition(nums, l, r);
    }else{
      r = p-1;
      p = partition(nums, l, r);
    }
  }
  return nums[p];
}

int main(){
  srand(time(NULL));
  vector<int> nums(100, 0); 
  for(int i = 0; i < 100; i++){
    nums[i] = rand()%100;
  }
  vector<int> num = nums;
  int k = rand()%100+1;
  
  chrono::steady_clock::time_point start
      = chrono::steady_clock::now();
  sort(num.begin(), num.end());
  cout<< k <<"th smallest by std::sort:   "<<num[k-1]<<endl;
  chrono::steady_clock::time_point end
      = chrono::steady_clock::now();
  chrono::microseconds t1 = chrono::duration_cast<chrono::microseconds>(end-start);
  
    
  start = chrono::steady_clock::now();
  int res = quickSelect(nums, k);
  cout<< k <<"th smallest by quickSelect: "<<res<<endl;
  end = chrono::steady_clock::now();
  chrono::microseconds t2 = chrono::duration_cast<chrono::microseconds>(end-start);
  
  cout<<"BENCHMARKING"
      <<endl<<"std::sort:   "<< t1.count() <<" us"
      <<endl<<"quickSelect: "<< t2.count() <<" us"
      <<endl;
}
