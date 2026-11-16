#include <iostream>
#include <bits/stdc++.h>

using namespace std;

{{SOLUTION}}



int main(){

    auto answer = Solution().{{FUNCTION}}();
    
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

// TreeNode* buildTree(string s) {
//     for (char& c : s) if (c == '[' || c == ']' || c == ',') c = ' ';
//     stringstream ss(s);
//     vector<string> v; string t;
//     while (ss >> t) v.push_back(t);
//     if (v.empty() || v[0] == "null") return nullptr;

//     TreeNode* root = new TreeNode(stoi(v[0]));
//     queue<TreeNode*> q; q.push(root);
//     for (int i = 1; i < v.size(); i += 2) {
//         TreeNode* cur = q.front(); q.pop();
//         if (v[i] != "null") q.push(cur->left = new TreeNode(stoi(v[i])));
//         if (i + 1 < v.size() && v[i + 1] != "null") q.push(cur->right = new TreeNode(stoi(v[i + 1])));
//     }
//     return root;
// }
