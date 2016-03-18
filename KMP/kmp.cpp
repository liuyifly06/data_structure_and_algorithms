#include "kmp.h"

void kmp::setPattern(string p){
    pattern = p;
    next = vector<int>(p.size(),0);
    GenerateNextTable();
}

void kmp::GenerateNextTable(){
    if(pattern.size() == 0){
        cout<<"Pattern String Can Not Be Empty !"<<endl;
        return;
    }
    int j = 0;
    int i = 1;
    next[0] = 0;
    while(i < next.size()){
        if(pattern[i] == pattern[j]){
            j++;
            next[i] = j;
            i++;
        }else{
            if(j != 0){
                j = next[j-1];
            }else{
                next[i] = j;
                i++;
            }
        }
    }
}

vector<int> kmp::search(string target){
    vector<int> location;
    if(target.size() == 0){
        cout<<"Target Can Not Be Empty !"<<endl;
        return location;
    }
    if(pattern.size() == 0){
        cout<<"Pattern String Can Not Be Empty !"<<endl;
        return location;
    }
    int N = target.size();
    int M = pattern.size();
    int i = 0;
    int j = 0;
    
    while(i < N){
        if(target[i] == pattern[j]){
            i++;
            j++;
        }
        if(j == M){
            location.push_back(i-M);
            j = next[j-1]; 
        }else if(i < N && target[i] != pattern[j]){
            if(j!=0) j = next[j-1];
            else i++;
        }
    }
    return location;
}
