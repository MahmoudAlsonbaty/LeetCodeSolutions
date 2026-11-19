#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

class Solution {
public:
    string digitSum(string s, int k) {
        if(s.length() <= k) return s;

        //S is larger
        string n ="";
        string currentGP = "";
        int currentSum = 0;
        for(int i =0;i<s.length();i++){
            if(i!= 0 && i%k == 0){
                currentGP = to_string(currentSum);
                n.append(currentGP);
                currentGP = "";
                currentSum = 0;
            }
            char c = s[i];
            currentSum += (c-'0');
            if(i == s.length()-1){
                currentGP = to_string(currentSum);
                n.append(currentGP);
                currentGP = "";
                currentSum = 0;
            }
        }
        if(n.length() > k){
            n = digitSum(n, k);
        }

        return n;
    }
};



int main(){
string s = "00000000";
int k = 3;
    auto answer = Solution().digitSum(s,k);
    
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
