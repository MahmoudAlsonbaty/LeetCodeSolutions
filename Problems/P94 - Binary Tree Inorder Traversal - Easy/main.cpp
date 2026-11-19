#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    void dfs(vector<int>* sol,TreeNode* curr){
        if(curr == nullptr) return;

        dfs(sol, curr->left);
        sol->push_back(curr->val);
        dfs(sol, curr->right);
        return;
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> sol;
        dfs(&sol,root);
        return sol;
    }
};



int main(){
    TreeNode* root = buildTree("[]");
    auto answer = Solution().inorderTraversal(nullptr);
    
    coutVector(&answer);
    return 0;
}

