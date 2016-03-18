/*
Suppose a machine with two variables (or registers) called X and Y, both containing the value 1.

The machine supports two operations: operation A is defined as X = X + Y and operation B is defined as Y = X + Y. 

Write a function returning the minimum number of operations needed for one of the registers to contain a target value T.

Example:
Input: 5
Output: 3. 

Explanation:
X Y
1 1    (starting state)


2 1    (operation A)
2 3    (operation B).
5 3    (operation A)

So it took 3 operations to reach 5 (and this happens to be the minimum number of operations needed).
*/

#include<iostream>
#include<climits>
#include<ctime>
using namespace std;

int minOperations(int target);

int minOperations(int A, int B);

int minOperations_(int target);

int minOperations_(int A, int B); 

int main(){
    int target = 0;
    bool END = false;
    while(!END){
        cout<<"Type the target value: "<<endl;
        cin>>target;
        cout<<"Minimum number of operations is:"<<endl;
        clock_t start = clock();
//        cout<<"Method 1 :"<<minOperations(target)<<endl;
        clock_t end1 = clock();
        cout<<"Method 2 :"<<minOperations_(target)<<endl;
        clock_t end2 = clock();
        double t1 = double(end1-start)/CLOCKS_PER_SEC;
        double t2 = double(end2-end1)/CLOCKS_PER_SEC;
        char end = 'y';
        cout<<"Time: METHOD1: "<<t1<<" METHOD2: "<<t2<<endl;
        cout<<"Continue ? (y)es / (n)o"<<endl;
        cin>>end;
        if(end == 'n') END = true;
    }
    return 0;
}

int minOperations(int target){
    if(target <= 0) return -1;
    if(target == 1) return 0;
    int count = target-1;
    for(int i = 1; i <= target/2; i++){
       int temp = minOperations(target-i,i);
       if(temp != INT_MAX) 
          count = min(count,temp + 1);
    }
    return count;
}

int minOperations(int A, int B){
    if(A == B || A < 1 || B < 1) return INT_MAX;
    if(B == 1) return A-1;
    if(A == 1) return B-1;
    int count = INT_MAX;
    for(int i = 1; i < B; i++){
       if((A-i)%B == 0){
          int temp = minOperations(B,i);
          if(temp != INT_MAX)
              count = min(count, (A-i)/B + minOperations(B,i));
       }
    }
    return count;
}

int minOperations_(int target){
    if(target <= 0) return -1;
    if(target == 1) return 0;
    int count = target-1;
    for(int i = 1; i <= target/2; i++){
       int temp = minOperations_(target-i,i);
       if(temp != INT_MAX) 
          count = min(count,temp + 1);
    }
    return count;
}

int minOperations_(int A, int B){
    if(A == B || A < 1 || B < 1) return INT_MAX;
    if(B == 1) return A-1;
    if(A == 1) return B-1;
    int count = INT_MAX;
    int temp = minOperations_(B, A%B);
    if(temp != INT_MAX)
         count = A/B + temp;
    return count;
}
