#include<iostream>
#include<string>
#include<vector>
using namespace std;
class kmp{
private:
    string pattern;
    vector<int> next;
public:
    kmp():pattern(""){};
    kmp(string p) : pattern(p){
        GenerateNextTable();
    }
    ~kmp(){next.clear(); pattern.clear();}
    void setPattern(string p);
    void GenerateNextTable();
    vector<int> search(string target);
};
