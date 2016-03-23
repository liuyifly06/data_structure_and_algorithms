#include"BinaryIndexTree.h"
#include<iostream>
#include<vector>

BinaryIndexTree::BinaryIndexTree(int size){
  BIT = vector<int>(size+1, 0);
} 

void BinaryIndexTree::update(int i, int value){
  i++;
  while(i < BIT.size()){
    BIT[i] += value;
    i += i&(-i);
  }
}

int BinaryIndexTree::getSum(int i){
  i++;
  int sum = 0;
  while(i > 0){
    sum += BIT[i];
    i -= i&(-i); 
  }
  return sum;
}
