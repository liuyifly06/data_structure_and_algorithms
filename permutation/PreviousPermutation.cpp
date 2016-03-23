#include<iostream>
#include<string>
using namespace std;

bool static comp(const char a, const char b){
  return a > b;
}

void swap(string & str, int i, int j){
  char temp = str[i];
  str[i] = str[j];
  str[j] = temp;
}

string previousPermutation(string str){
  if(str.size() < 2) return str;
  int larger = -1;
  for(int i = str.size()-1; i >= 1; i--){
    if(str[i] < str[i-1]){
      larger = i-1;
      break; 
    }
  }
  if(larger == -1){
    sort(str.begin(), str.end(), comp);
    return str;
  }
  int smaller = str.size()-1;
  for(int i = larger + 1; i < str.size(); i++){
    if(str[i] > str[larger]){
      smaller = i-1;
      break; 
    }
  }
  swap(str, larger, smaller);
  sort(str.begin()+larger+1, str.end(), comp);
  return str;
}

int main(){
  bool run = true;
  while(run){
    string test;
    cout<<endl<<"Type the test string: ";
    cin >> test;
    cout<<"Previous permutaion is: "
        <<previousPermutation(test)<<endl;
    cout<<"Continue? y/n"<<endl;
    char c;
    cin >> c;
    if(c == 'n') run = false;
  }
}
