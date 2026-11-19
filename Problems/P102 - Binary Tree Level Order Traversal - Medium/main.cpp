#include <iostream>
#include <bits/stdc++.h>

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> sol;
        queue<pair<TreeNode*,int>> q;
        if(root == nullptr) return sol;
        q.push(make_pair(root,0));
        while(!q.empty()){
            TreeNode* curr= q.front().first;
            int currLevel = q.front().second;
            q.pop();
            if(sol.size()<=currLevel){
                sol.push_back({curr->val});
            }else{
                sol[currLevel].push_back(curr->val);
            }

            if(curr->left != nullptr){
                q.push(make_pair(curr->left,currLevel+1));
            }
            if(curr->right != nullptr){
                q.push(make_pair(curr->right,currLevel+1));
            }
        }

        return sol;
    }
};


TreeNode* buildTree(string s) ;
int main(){
    string case1 = "[3,9,20,null,null,15,7]";
    TreeNode* root = buildTree(case1);
    auto answer = Solution().levelOrder(new TreeNode(1));
    
    for(int i = 0;i<answer.size();i++){
        cout << endl;
        for(int j = 0;j<answer[i].size();j++){
            cout<< answer[i][j] << " ";
        }
    }
    // for(int i = 0;i<answer.size();i++){
    //     cout<< answer[i] << " ";
    // }
    // std::cout << answer <<endl;
    return 0;
}

TreeNode* buildTree(string s) {
    for (char& c : s) if (c == '[' || c == ']' || c == ',') c = ' ';
    stringstream ss(s);
    vector<string> v; string t;
    while (ss >> t) v.push_back(t);
    if (v.empty() || v[0] == "null") return nullptr;

    TreeNode* root = new TreeNode(stoi(v[0]));
    queue<TreeNode*> q; q.push(root);
    for (int i = 1; i < v.size(); i += 2) {
        TreeNode* cur = q.front(); q.pop();
        if (v[i] != "null") q.push(cur->left = new TreeNode(stoi(v[i])));
        if (i + 1 < v.size() && v[i + 1] != "null") q.push(cur->right = new TreeNode(stoi(v[i + 1])));
    }
    return root;
}
