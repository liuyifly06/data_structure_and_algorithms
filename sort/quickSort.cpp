#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

void swap(vector<int> & nums, int i, int j){
  int temp = nums[i];
  nums[i] = nums[j];
  nums[j] = temp;
}

int partition(vector<int> & nums, int l, int r){
  int p = l-1;
  int pivot = nums[r];
  for(int i = l; i <= r; i++)
    if(nums[i] <= pivot)
      swap(nums, ++p, i);
  return p;
}

void quickSort(vector<int> & nums, int l, int r){
  if(l < r){
    int p = partition(nums, l, r);
    quickSort(nums, l, p-1);
    quickSort(nums, p+1, r);
  }
}

void quickSort(vector<int> & nums){
  int left = 0;
  int right = nums.size()-1;
  quickSort(nums, left, right);

}

int main(){
  srand(time(NULL));
  int totalNumber = 10;
  vector<int> nums;
  for(int i = 0; i < totalNumber; i++){
    nums.push_back(rand()%totalNumber);
  }
  
  vector<int> nums_backup = nums;
  quickSort(nums);
  sort(nums_backup.begin(), nums_backup.end());
  
  cout<<"Sorted by my algorithm: "; 
  for(int i = 0; i < totalNumber; i++) cout<<" "<<nums[i];
  cout<<endl<<"Sorted by C++ std::sort:";
  for(int i = 0; i < totalNumber; i++) cout<<" "<<nums_backup[i];
  cout<<endl;
}
