#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Combine the two hashes safely
        return h1 ^ (h2 << 1);
    }};
    public:
    bool dfs(vector<vector<char>>& grid,unordered_map<pair<int,int>,pair<int,int>,PairHash>& currentPath,pair<int,int> point,pair<int,int> parent){
        if(currentPath.count(point) != 0) return true;
        
        int fir = point.first;
        int sec = point.second;

        bool top= false; 
        bool left= false; 
        bool right= false; 
        bool bottom= false; 

        // currentPath.push_back(make_pair(fir,sec));
        // int size = currentPath.size();
        
        //top 
        int topY = fir-1;
        int topX = sec;
        if(topY >= 0 && grid[topY][topX] == grid[point.first][point.second] && parent != make_pair(topY,topX)){
            currentPath[point] = make_pair(topY,topX);
            top = dfs(grid,currentPath,make_pair(topY,topX),point);
            // currentPath.resize(size);
        } 

        //left 
        int leftY = fir;
        int leftX = sec-1;
        if(leftX >= 0 && grid[leftY][leftX] == grid[point.first][point.second] && parent != make_pair(leftY,leftX)){
            currentPath[point] = make_pair(leftY,leftX);
            // currentPath.resize(size);
            left = dfs(grid,currentPath,make_pair(leftY,leftX),point);
        } 

        //right 
        int rightY = fir;
        int rightX = sec+1;
        if(rightX < grid[rightY].size() && grid[rightY][rightX] == grid[point.first][point.second] && parent != make_pair(rightY,rightX)){
            currentPath[point] = make_pair(rightY,rightX);
            // currentPath.resize(size);
            right = dfs(grid,currentPath,make_pair(rightY,rightX),point);
        } 

        //bottom 
        int bottomY = fir+1;
        int bottomX = sec;
        if(bottomY < grid.size() && grid[bottomY][bottomX] == grid[point.first][point.second] && parent != make_pair(bottomY,bottomX)){
            currentPath[point] = make_pair(bottomY,bottomX);
            // currentPath.resize(size);
            bottom = dfs(grid,currentPath,make_pair(bottomY,bottomX),point);
            
        }
        
        grid[point.first][point.second] = 'Z';
        if(top || bottom || left || right) return true;

        return false;

    }
    bool searchPath(vector<pair<int,int>>& path,pair<int,int>point){
        for(auto t: path){
            if(t == point){
                return true;
            }
        }
        return false;
    }

    bool containsCycle(vector<vector<char>>& grid) {
        // unordered_map<pair<int,int>,bool> explored;
        bool found = false;
        for(int i = 0;i<grid.size();i++){
            for(int j = 0;j<grid[i].size();j++){
                if(grid[i][j] != 'Z'){
                    unordered_map<pair<int,int>,pair<int,int>,PairHash> path ={};
                    found = dfs(grid,path,make_pair(i,j),make_pair(-1,-1));
                    if(found) return true;
                }    
            } 
        }
        return false;
    }
};



int main(){
    vector<vector<char>> grid = {{'a', 'a', 'a', 'a'}, {'a', 'b', 'b', 'a'}, {'a', 'b', 'b', 'a'}, {'a', 'a', 'a', 'a'}};
    // vector<vector<char>> grid = {{'a', 'a', 'a'}, {'b', 'z', 'b'}, {'b', 'b', 'a'}};
    // vector<vector<char>> grid = {{'c', 'c', 'c', 'a'}, {'c', 'd', 'c', 'c'}, {'c', 'c', 'e', 'c'}, {'f', 'c', 'c', 'c'}};
    auto answer = Solution().containsCycle(grid);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // for(int i = 0;i<answer.size();i++){
    //     cout<< answer[i] << " ";
    // }
    std::cout << answer <<endl;
    return 0;
}

// TreeNode* buildTree(string s) {
//     for (char& c : s) if (c == '[' || c == ']' || c == ',') c = ' ';
//     stringstream ss(s);
//     vector<string> v; string t;
//     while (ss >> t) v.push_back(t);
//     if (v.empty() || v[0] == "null") return nullptr;

//     TreeNode* root = new TreeNode(stoi(v[0]));
//     queue<TreeNode*> q; q.push(root);
//     for (int i = 1; i < v.size(); i += 2) {
//         TreeNode* cur = q.front(); q.pop();
//         if (v[i] != "null") q.push(cur->left = new TreeNode(stoi(v[i])));
//         if (i + 1 < v.size() && v[i + 1] != "null") q.push(cur->right = new TreeNode(stoi(v[i + 1])));
//     }
//     return root;
// }
