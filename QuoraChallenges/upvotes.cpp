#include<iostream>
#include<cstring>
using namespace std;


int numInterval(int length){
  return length*(length-1)/2;
}

void addData(int* metric, int n, int k, int start, int end, int sign);

void addData(int* metric, int n, int k, int start, int end, int sign){
  int start_index = start / k;
  int end_index   = end / k;
  if(start_index == end_index){
    metric[start_index] += sign * numInterval(end-start+1); 
  }else{
    int s_end = (end / k) * k - 1;
    int e_start = (end / k) * k;  
    metric[start_index] += sign 
  }
int* upvotesMetric(int* upvotes, int n, int k);


int main(){
	int n = 0; // number of days
	int k = 0; // window size
  int* upvotes = new int [n]; 
  cin >> n >> k;
  for(int i = 0; i < n; i++){
    cin >> upvotes[i];
  }
  
  int* metric = upvotesMetric(upvotes, n, k); 
  
  for(int i = 0; i < n-k+1; i++){
    cout << metric[i]<<endl;
  }
  
  delete[] upvotes;
  delete[] metric;
  return 0;
};


int* upvotesMetric(int* upvotes, int n, int k){
  int index = 1; // current day  
  
  int* metric = int new[n-k+1];// return value
  memset(metric, 0, sizeof(int)*(n-k+1)); // initialize
  if(k == 1) return metric; // no need for calculation of k == 1
 
  bool in = false, decreasing = false; // indicating status
  int lenIncrease = 1, lenDecrease = 1; // length of status
  Q.push_back(0);

  while(index < n){ // go though data of every day;
    while(daysInQueue < k){
      //calculate length of nondecreaing / nonincreasing days
      
      if(upvotes[index] == upvotes[index-1]){
        decreasing = true; increasing = true;
        lenDecrease++; lenIncrease++;
        daysInQueue++; *Q.rbegin() = lenDecrease
      }
      

      if(upvotes[index] > upvotes[index-1] && (index == 1 || 
          !increasing )){ // nonincreasing changes to nondecreasing
        
        if(index != 1){// push the decreasing range;
          Q.push_back(lenDecrease);
          daysInQueue++;
          lenDecrease = 1;
          decreasing = false;
        } 
        increasing = true;
        lenIncrease = 2;
      }else if(upvotes[index] < upvotes[index-1] && (index == 1 || 
          !decreasing )){ // nondecreasing changes to nonincreasing
        
        if(index != 1){// push the decreasing range;
          Q.push_back(lenincrease);
          daysInQueue++;
          lenIncrease = 1;
          increasing = false;
        } 
        decreasing = true;
        lenDecrease = 2;
      }

       
      
    }
  }

  
  return metric;
}

