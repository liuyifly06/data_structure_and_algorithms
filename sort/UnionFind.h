#ifndef UNIONFIND_H
#define UNIONFIND_H

#include<iostream>
#include<vector>
using namespace std;

class UnionFind{
  private:
    vector<int> ID;
    vector<int> SZ;
    int count;
    int root(int i);
  public:
    UnionFind(int size);
    void Union(int i, int j);
    bool find(int i, int j);
};
#endif
