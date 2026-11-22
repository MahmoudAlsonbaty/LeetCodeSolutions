#pragma once
#include <bits/stdc++.h>
#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

using namespace std;

inline TreeNode *buildTree(string s) {
  for (char &c : s)
    if (c == '[' || c == ']' || c == ',')
      c = ' ';
  stringstream ss(s);
  vector<string> v;
  string t;
  while (ss >> t)
    v.push_back(t);
  if (v.empty() || v[0] == "null")
    return nullptr;

  TreeNode *root = new TreeNode(stoi(v[0]));
  queue<TreeNode *> q;
  q.push(root);
  for (int i = 1; i < v.size(); i += 2) {
    TreeNode *cur = q.front();
    q.pop();
    if (v[i] != "null")
      q.push(cur->left = new TreeNode(stoi(v[i])));
    if (i + 1 < v.size() && v[i + 1] != "null")
      q.push(cur->right = new TreeNode(stoi(v[i + 1])));
  }
  return root;
}
template <typename T> void cout2DVector(vector<vector<T>> *answer) {
  for (size_t i = 0; i < answer->size(); i++) {
    cout << endl;
    for (size_t j = 0; j < (*answer)[i].size(); j++) {
      cout << (*answer)[i][j] << ", ";
    }
  }
}
template <typename T> void coutVector(vector<T> *answer) {
  for (size_t i = 0; i < answer->size(); i++) {
    cout << (*answer)[i] << ", ";
  }
}
template <typename T> void coutBool(T *answer) {
  if(*answer == 0){
    cout << "False" <<endl;
  }else{
    cout << "True" <<endl;
  } 
} 
