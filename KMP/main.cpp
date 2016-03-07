#include<iostream>
#include<vector>
#include<string>
#include"kmp.h"

void print(vector<int> content, string target, string pattern){
    cout<<"Searching pattern: ["<<pattern<<"]"<<endl;
    cout<<"Searching in: ["<<target<<"]"<<endl;
    cout<<"Searching result: "<<endl;
    for(int i = 0; i < content.size(); i++){
        cout<<"at index:  "<<content[i]<<" {"
            <<target.substr(content[i], int(pattern.size()))
            <<"} "<<endl;
    }
}

int main(){
    vector<int> find;
    vector<string> pattern;
    pattern.push_back("love");
    pattern.push_back("No");
    pattern.push_back("I");
    pattern.push_back("what");
    kmp test;
    
    for(int i = 0; i < pattern.size(); i++){
        test.setPattern(pattern[i]);
        string target = "No matter what has happened. No matter what you’ve done. No matter what you will do. I will always love you. I swear it.";
        find = test.search(target);
        print(find, target, pattern[i]);
    }
    return 0;  
}
