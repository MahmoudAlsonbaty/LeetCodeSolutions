#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> sol;
        preorderDFS(sol,root);
        return sol;
    }
    void preorderDFS(vector<int>&res,TreeNode* node){
        if(node == nullptr) return;
        res.push_back(node->val);
        preorderDFS(res, node->left);
        preorderDFS(res, node->right);
    }
};



int main(){

    // auto answer = Solution().preorderTraversal();
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
