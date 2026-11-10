#include <cstdint>
#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        queue<pair<TreeNode*,int>> q;
        q.push(make_pair(root, 1));
        vector<vector<TreeNode*>> levels;
        while(!q.empty()){
            TreeNode* curr = q.front().first;
            int level = q.front().second;
            q.pop();
            if(levels.size() < level){
                levels.push_back({curr});
            }else{
                levels[level-1].push_back(curr);
            }
            if(curr->val == INT32_MIN) continue;
            if(curr->left != nullptr){
                q.push(make_pair(curr->left,level+1));
            }else{
                q.push(make_pair(new TreeNode(INT32_MIN),level+1));
            }

            if(curr->right != nullptr){
                q.push(make_pair(curr->right,level+1));
            }else{
                q.push(make_pair(new TreeNode(INT32_MIN),level+1));
            }
            
        }
        for(int i = 0;i<levels.size();i++){
            int j = levels[i].size()-1;
            for(int m = 0;m<levels[i].size()/2;m++){
                if(levels[i][m]->val != levels[i][j]->val){
                    return false;
                }
                if(j-1 >= 0) j--;
            }   
        }
        return true;

    }
};

int main(){
    TreeNode* root = new TreeNode(1,new TreeNode(2,nullptr,new TreeNode(4)),new TreeNode(2,nullptr,new TreeNode(4)));
    auto answer = Solution().isSymmetric(root);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
