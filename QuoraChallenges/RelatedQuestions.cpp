#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<climits>
using namespace std;

// build graph according to edges
unordered_map<int, unordered_set<int>> buildGraph(vector<vector<int>> & edges){
  unordered_map<int, unordered_set<int>> graph;
  for(int i = 0; i < edges.size(); i++){
    graph[edges[i][0]].insert(edges[i][1]);
    graph[edges[i][1]].insert(edges[i][0]);
  }
  return graph;
}

// find root of lowest tree (weighted)
/*
-----------------Why root of tree ?----------
  The graph is actually a tree and there are a 
lot of nodes in the graph that can be the root
of a tree. In this question, we need to find a
root that the hight of the tree is minimized. 
Of course, one should considering the "reading
time weight" for calculating the tree height. 
*/
int rootOfTree(unordered_map<int, unordered_set<int>> & graph, vector<int> & times){
  if(graph.size() <= 1) return 1;
  vector<int> time = times;
  
  int min_life = INT_MAX;
  queue<int> leaves;
  for(auto it = graph.begin(); it != graph.end(); it++){
    if(it->second.size() == 1){ // if the node is leaf;
      leaves.push(it->first);
      min_life = min(min_life, time[it->first]);
    }
  }
  
  // start from all the leaves, removing nodes  using BFS 
  while(!leaves.empty() && graph.size() > 2){
    int n = leaves.size();
    int next_min_life = INT_MAX;
    for(int i = 0; i < n; i++){
      int node = leaves.front();
      leaves.pop();
      time[node] -= min_life;
      if(time[node] <= 0){
        int corr_node = *(graph[node].begin()); 
        graph[corr_node].erase(node);
        if(graph[corr_node].size() == 1){
          leaves.push(corr_node);
          next_min_life = min(next_min_life, time[corr_node]);
        }
        graph.erase(node);
      }else{
        leaves.push(node);
        next_min_life = min(next_min_life, time[node]);
      }
    }
    min_life = next_min_life;
  }
  
  // return the optimal root
  // only one node left
  if(graph.size() == 1) return graph.begin()->first;
  // two nodes left
  auto it = graph.begin(); it++;
  if(time[it->first] == time[graph.begin()->first])
    return times[it->first] > times[graph.begin()->first] ? graph.begin()->first : it->first;
  else if(time[it->first] < time[graph.begin()->first]) return it->first;
  else return graph.begin()->first; 
}


int main(){
  // number of questions;
  int n = 0;
  cin >> n;
  
  // reading time of questions;
  vector<int> time(n+1, 0);
  for(int i = 0; i < n; i++){
    cin >> time[i+1];
  }
 
  // relationship between questions;
  vector<vector<int>> edges(n, vector<int>(2, 0));
  for(int i = 0; i < n-1; i++){
    cin >> edges[i][0] >> edges[i][1];
  }

  //build graph
  unordered_map<int, unordered_set<int>> graph = buildGraph(edges);

  //find lowest tree root (weighted)
  cout << rootOfTree(graph, time) << endl;
}