#ifndef BINARYINDEXTREE_H
#define BINARYINDEXTREE_H
#include<iostream>
#include<vector>
using namespace std;

class BinaryIndexTree{
  vector<int> BIT;
  public:
    BinaryIndexTree(int size);
    void update(int i, int value);
    int getSum(int i);
};

#endif
