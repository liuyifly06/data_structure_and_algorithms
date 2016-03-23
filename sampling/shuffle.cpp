#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

void swap(vector<int> & num, int i, int j){
  int temp = num[i];
  num[i] = num[j];
  num[j] = temp;
}

void shuffle(vector<int> & cards){
  for(int i = 1; i < cards.size(); i++){
    int j = rand()%(i+1);
    swap(cards, j, i);
  }
}

int main(){
  srand(time(NULL));
  vector<int> cards(54, 0);
  for(int i = 0; i < cards.size(); i++) cards[i] = i+1;
  shuffle(cards);
  for(int i = 0; i < cards.size(); i++){
    if(i%13 == 0) cout<<endl;
    cout<<cards[i]<<" ";
  }
  cout<<endl;
  return 0;
}
