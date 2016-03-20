#include<iostream>
#include<cstring>
#include<list>
using namespace std;

struct interval{
  // start_day, end_day and sign for increasing/decreasing
  int start; int end; int sign;
  interval(int s, int e, int si): start(s), end(e), sign(si){};
};

int numInterval(int length);

void push(list<interval> & intervals, int start, int end, int sign);

void calculateSum(list<interval> & intervals, int currentDay);

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


int calculateSum(list<interval> & intervals, int sum, int currentDay, int k){
  // no interval expired
  if(intervals.empty() || currentDay < intervals.begin()->start + k) return sum; 
  
  // eliminate all the expried intervals
  while(!intervals.empty() && intervals.begin()->end + k - 1 <= currentDay){
//    cout<<"eliminating expired"<<endl;
    int length = intervals.begin()->end - intervals.begin()->start + 1;
    sum -= numInterval(length) * (intervals.begin()->sign);
    intervals.erase(intervals.begin());
  }
  
  // modify partially expired intervals
  list<interval>::iterator it = intervals.begin();
  while(it != intervals.end() && it->start + k - 1 < currentDay){
//    cout<<"modify partially expired"<<endl;
    // subtract old numbers 
    int length = it->end - it->start + 1;
    sum -= numInterval(length) * (it->sign);
    
    // add new numbers
    it->start = currentDay - k + 1;
    length = it->end - it->start + 1;
    sum += numInterval(length) * (it->sign);
    // go to next interval
    it++;
  }
  
/*  cout<<"start "<<intervals.begin()->start
      <<" end "<<intervals.begin()->end
      <<" sign "<<intervals.begin()->sign
      <<" sum "<<sum<<endl;//*/
  return sum;
}

void push(list<interval> & intervals, int start, int end, int sign){
  interval temp = interval(start, end, sign);
  intervals.push_back(temp);
}

int* upvotesMetric(int* upvotes, int n, int k){
  // Return array 
  int* metric = new int[n-k+1];
  // Initialize return array 
  memset(metric, 0, sizeof(int)*(n-k+1));

  // Window size == 1, no need for calculation 
  if(k == 1) return metric;

  //Indicator of current interval status 
  bool in_status = false, de_status = false;
  //Start and end day of current interval
  int in_start = 0,  in_end = 0, de_start = 0, de_end = 0;
  //Containter for all the intervals in k days
  list<interval> intervals;

  // metric for current window
  int metric_current = 0;

  // Go through data of every day
  for(int i = 1; i < n; i++){
    //update current interval start position
    in_start = max(in_start, i - k + 1);
    de_start = max(de_start, i - k + 1);
    // Condition for start recording interval    
    if(upvotes[i] >= upvotes[i-1] && !in_status){
      in_start = i-1; in_status = true;
    }
    if(upvotes[i] <= upvotes[i-1] && !de_status){
      de_start = i-1; de_status = true;
    }
    // Interval ends
    if(upvotes[i] <  upvotes[i-1] && in_status){
      in_end = i-1;   in_status = false;
      push(intervals, in_start, in_end, 1);
      metric_current += numInterval(in_end - in_start + 1);
    }
    if(upvotes[i] >  upvotes[i-1] && de_status){
      de_end = i-1;   de_status = false;
      push(intervals, de_start, de_end, -1);
      metric_current -= numInterval(de_end - de_start + 1);
    }

    // update metric for current window
    metric_current = calculateSum(intervals, metric_current, i, k);
    int current_in = in_status ? numInterval(i - in_start + 1) : 0;
    int current_de = de_status ? numInterval(i - de_start + 1) : 0;
/*    cout<<"current in list: "<<metric_current<<" in_status "<<
        (in_status ? "T" : "F") <<" de_status "<<(de_status ? "T" : "F")
        <<" in: "<<current_in<<" de: "<<current_de<<endl;//*/
    metric[(i-k < 0) ? 0 : i-k+1] = metric_current + current_in - current_de;
  }
  return metric;
}

int numInterval(int length){
  if(length <= 1) return 0;
  else return length*(length-1)/2;
}
