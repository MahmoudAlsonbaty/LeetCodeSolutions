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
    unordered_map<TreeNode*,pair<int,int>> minMax;
    unordered_map<TreeNode*,bool> validBS;
    unordered_map<TreeNode*,int> sumOfSubtree;
    int maxi = INT32_MIN;
    
    int dfs(TreeNode* node){
        if(node == nullptr) return 0;

        int left = dfs(node->left);
        int right = dfs(node->right);

        int sum = node->val + left + right;
        if(validBS[node]){
            maxi = max(maxi,sum);
        }
        sumOfSubtree[node] = sum;
        return sum;
    }

    
    bool validTree(TreeNode* root, int mainRootVAl){
        if(root == nullptr) return true;
        bool left = true;
        bool right = true;

        if(root->left) left = validTree(root->left,mainRootVAl);
        if(root->right) right = validTree(root->right,mainRootVAl);
        
        if(!left || !right) return false;

        bool leftBalanced = true;
        bool rightBalanced = true;
        if(root->left){
            if(minMax[root->left].second >= root->val){
                return false;
            }
            if(root->left->val < root->val){
                leftBalanced = true;
            }else{
                leftBalanced = false;
            }
        }
        if(root->right){
            if(minMax[root->right].first <= root->val){
                return false;
            }
            if(root->right->val > root->val){
                rightBalanced = true;
            }else{
                rightBalanced = false;
            }
        }
        if(leftBalanced && rightBalanced){
            validBS[root] = true;
            return true;
        }  
        return false;
    }
    pair<int,int> getMinMax(TreeNode* node){
        if(node == nullptr) return make_pair<int,int>(INT32_MAX,INT32_MIN);

        pair<int,int> left,right;
        left = getMinMax(node->left);
        right = getMinMax(node->right);

        minMax[node] = make_pair(min(node->val,min(left.first,right.first)),max(node->val,max(left.second,right.second)));

        return minMax[node];
    }

    int maxSumBST(TreeNode* root) {
        getMinMax(root);
        validTree(root,root->val);
        dfs(root);
        if(maxi < 0) return 0;
        return maxi;

    }
};


TreeNode* buildTree(string s) ;

int main(){
    TreeNode* root = buildTree("[1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]");
    auto answer = Solution().maxSumBST(root);
    
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
