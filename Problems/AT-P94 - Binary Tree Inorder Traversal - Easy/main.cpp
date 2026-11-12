#include <cstddef>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;


// Definition for a binary tree node.
typedef struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
}TreeNode;

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        if(root->left !=nullptr) s.push(root->left);
        while (!s.empty()) {
            TreeNode* curr = s.top();
            if(curr->left!= nullptr) s.push(curr->left);
            s.push(curr);
            if(curr->right!= nullptr) s.push(curr->right);
            
        }
    }
};

int main(){

    auto answer = Solution().inorderTraversal();
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
