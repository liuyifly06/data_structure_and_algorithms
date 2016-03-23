#include<iostream>
#include<vector>
#include"UnionFind.h"
using namespace std;    

UnionFind::UnionFind(int size){
  ID = vector<int>(size, 0);
  SZ = vector<int>(size, 1);
  for(int i = 0; i < size; i++) ID[i] = i;
  count = size;
}

int UnionFind::root(int i){
  while(i != ID[i]){
    ID[i] = ID[ID[i]];
    i = ID[i];
  }
  return i;
} 

void UnionFind::Union(int i, int j){
  int r_i = root(i);
  int r_j = root(j);
  if(r_i == r_j) return;
  if(SZ[r_i] > SZ[r_j]){
    ID[r_j] = r_i;
    SZ[r_i] += SZ[r_j];
  }else{
    ID[r_i] = r_j;
    SZ[r_j] += SZ[r_i];
  }
  count--;
}
    
bool UnionFind::find(int i, int j){
  return root(i) == root(j);
}

