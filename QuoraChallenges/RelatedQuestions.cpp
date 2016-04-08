#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<utility>
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

// find root of lowest tree 
int rootOfTree(unordered_map<int, unordered_set<int>> & graph, vector<int> & time){
  if(graph.size() <= 1) return 1;
  
  //for remembering indegree
  vector<int> indegree(time.size(), 0);
  
  //BFS
  queue<int> leaves;
  for(auto it = graph.begin(); it != graph.end(); it++){
    if(it->second.size() == 1){ // if the node is leaf;
      leaves.push(it->first);
      indegree[it->first] = 1;
    }
  }
  bool start = false;
  // start from all the leaves, removing nodes  using BFS 
  while(leaves.size() > 2 || (graph.size() > 2 && !start)){
    int n = leaves.size();
    for(int i = 0; i < n; i++){
      int node = leaves.front();
      int inDe = indegree[node];
      leaves.pop();
      if(graph[node].size() > 0){
        int corr_node = *(graph[node].begin());
        indegree[corr_node] += inDe; 
        graph[corr_node].erase(node);
        if(graph[corr_node].size() == 1){
          leaves.push(corr_node);
        }
        graph.erase(node);
      }
    }
    start = true;
  }
  

  if(leaves.size() == 0) return 0;
  // return the optimal root
  // only one node left
  if(leaves.size() == 1) return leaves.front();
  // two nodes left
  // Choose the node with larger indegree
  int first  = leaves.front(); leaves.pop();
  int second = leaves.front(); leaves.push(first); 
  if(indegree[first] != indegree[second]){
    return indegree[first] > indegree[second] ? first : second;
  }else{
    int min_node = time[first] < time[second] ? first : second;
    while(!leaves.empty()){
      int current = leaves.front();
      leaves.pop();
      if(time[current] < time[min_node])
        min_node = current;
      if(graph[current].size() > 1)
        cout<<"Error: outDegree > 2 at final stage"<<endl;
      for(auto it = graph[current].begin(); it != graph[current].end(); it++){
        leaves.push(*it);
        graph[*it].erase(current);
      }
      graph.erase(current);
    }
    return min_node;  
  }  
  
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
  vector<vector<int>> edges(n-1, vector<int>(2, 0));
  for(int i = 0; i < n-1; i++){
    cin >> edges[i][0] >> edges[i][1];
  }

  //build graph
  unordered_map<int, unordered_set<int>> graph = buildGraph(edges);

  //find lowest tree root (weighted)
  cout << rootOfTree(graph, time) << endl;
}

