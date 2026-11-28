#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> sol;
        postorderDFS(sol,root);
        return sol;
    }
    void postorderDFS(vector<int>&res,TreeNode* node){
        if(node == nullptr) return;
        postorderDFS(res, node->left);
        postorderDFS(res, node->right);
        res.push_back(node->val);
    }
};



int main(){

    // auto answer = Solution().postorderTraversal();
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
