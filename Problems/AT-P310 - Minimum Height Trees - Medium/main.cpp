#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    int dfs(int n, vector<vector<int>>&){
        
    }
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        //          height , node
        vector<pair<int,int>> heights;
        unordered_map<int,vector<int>> adj;
        for(auto t:edges){
            adj[t[0]].push_back(t[1]);
            adj[t[1]].push_back(t[0]);
        }

        for(int i = 0;i<n;i++){
            unordered_map<int,bool> visited;

            //.       node height
            stack<pair<int,int>> s;
            int myHeight = 0;
            s.push(make_pair(i,0));
            while(!s.empty()){
                int currNode = s.top().first;
                int currHeight = s.top().second;
                s.pop();
                myHeight = max(myHeight,currHeight);

                visited[currNode] = true;
                for(auto t: adj[currNode]){
                    if(visited[t] == true) continue;
                    s.push(make_pair(t,currHeight+1));
                }
            }
            heights.push_back(make_pair(myHeight,i));
        }
        
        sort(heights.begin(),heights.end());
        vector<int> sol;
        int prev = heights[0].first;
        for(int i = 0;i<heights.size();i++){
            if(prev == heights[i].first){
                sol.push_back(heights[i].second);
                prev = heights[i].first;
            }else{
                break;
            }
        }
        return sol;
    }
};



int main(){
    int n = 4;
vector<vector<int>> edges = {{1, 0}, {1, 2}, {1, 3}};
    auto answer = Solution().findMinHeightTrees(n,edges);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
