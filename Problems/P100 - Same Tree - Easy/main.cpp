#include <iostream>
#include <bits/stdc++.h>
#include <queue>

using namespace std;


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode* right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode* left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<TreeNode*> p1;
        queue<TreeNode*> q1;
        p1.push(p);
        q1.push(q);
        while (!p1.empty()) {
            TreeNode* t = p1.front();
            p1.pop();
            TreeNode* c = nullptr;
            if(!q1.empty()){
                c = q1.front();
                q1.pop();
            }
            if((t == nullptr && c != nullptr )||(c == nullptr && t != nullptr )) return false;
            if(t== nullptr && c == nullptr) continue;
            if(t->val != c->val){
                return false;
            }else {
                p1.push(t->left);
                p1.push(t->right);
                q1.push(c->left);
                q1.push(c->right);
            }
        }
        return true;
    }
};

int main(){

    // auto answer = Solution().isSameTree();
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // for(int i = 0;i<answer.size();i++){
    //     cout<< answer[i] << " ";
    // }
    // std::cout << answer <<endl;
    return 0;
}
