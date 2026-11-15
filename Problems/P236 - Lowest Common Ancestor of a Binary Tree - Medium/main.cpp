#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root==nullptr){
            return nullptr;
        }
        if(root == p || root == q){
            return root;
        }
        //Explore left
        TreeNode* toLeft = dfs(root->left,p,q);
        //Explore left
        TreeNode* toRight = dfs(root->right,p,q);

        if(toLeft != nullptr && toRight != nullptr){
            return root;
        }else if(toRight == nullptr){
            return toLeft;
        }else if (toLeft == nullptr) {
            return toRight;
        }

        return nullptr;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return dfs(root, p, q);
    }
};

int main(){
    TreeNode* root = new TreeNode(3);
    TreeNode* c1 = new TreeNode(5);
    TreeNode* c2 = new TreeNode(1);
    TreeNode* c3 = new TreeNode(6);
    TreeNode* c4 = new TreeNode(2);
    TreeNode* c5 = new TreeNode(0);
    TreeNode* c6 = new TreeNode(8);
    TreeNode* c7 = new TreeNode(7);
    TreeNode* c8 = new TreeNode(4);
    root->left = c1;
    root->right = c2;
    c1->left = c3;
    c1->right = c4;
    c4->left = c7;
    c4->right = c8;
    c2->left = c5;
    c2->right = c6;
    auto answer = Solution().lowestCommonAncestor(root,c1,c8);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // for(int i = 0;i<answer.size();i++){
    //     cout<< answer[i] << " ";
    // }
    std::cout << answer->val <<endl;
    return 0;
}
