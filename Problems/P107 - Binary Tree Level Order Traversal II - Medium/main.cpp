#include <iostream>
#include <bits/stdc++.h>

using namespace std;
    // Definition for singly-linked list.
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        
        queue<pair<TreeNode*,int>> q;
        q.push(make_pair(root,1));
        vector<vector<int>> levels;

        while(!q.empty()){
            TreeNode* curr = q.front().first;
            if(curr == nullptr){
                q.pop();
                continue;
            }
            int currLevel = q.front().second;
            if(levels.size() <= currLevel-1){
                levels.push_back({curr->val});
            }else{
                levels[currLevel-1].push_back(curr->val);
            }

            q.pop();

            if(curr->left != nullptr){
                q.push(make_pair( curr->left,currLevel+1));
            }
            if(curr->right != nullptr){
                q.push(make_pair( curr->right,currLevel+1));
            }
        }
        vector<vector<int>> rev;
        for(int i = levels.size()-1;i>=0;i--){
            rev.push_back(levels[i]);
        }
        return rev;

    }
};


int main(){
    TreeNode* root = new TreeNode(3,new TreeNode(9),new TreeNode(20,new TreeNode(15),new TreeNode(7)));
     auto answer = Solution().levelOrderBottom(root);

    for(int i = 0;i<answer.size();i++){
        cout << endl;
        for(int j = 0;j<answer[i].size();j++){
            cout<< answer[i][j] << " ";
        }
    }
    return 0;
}
