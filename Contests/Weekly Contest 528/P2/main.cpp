#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bits/stdc++.h>
#include <iterator>
#include <vector>

using namespace std;
class Solution {
    typedef struct Node{
        int score;
        Node* parent;
        bool hasReset = false;
        vector<Node*> children;
        int op;
        int subtreeValue;
        int level;
    }Node;

public:
    int dfs(Node* root, int level){
        if(root == nullptr) return 0;
        root->level = level;
        int sum = 0;
        for(auto t:root->children){
            if(t->hasReset) continue;
            sum += dfs(t,level+1);
        }
        root->subtreeValue = root->score + sum;
        
        return root->subtreeValue;
    }
    bool hasSelfOrParentReset(Node* node){
        Node* p = node;
        while(p){
            if(p->hasReset == true) return true;
            p = p->parent;
        }
        return false;
    }
    int maxScore(vector<int>& parent, vector<int>& op, vector<int>& score) {
        vector<Node*> Nodes(parent.size());
        for(int i = 0;i<parent.size();i++) Nodes[i] = new Node();

        Nodes[0]->parent = nullptr;
        Nodes[0]->score = score[0];
        Nodes[0]->op = op[0];
        Nodes[0]->level = 0;
        vector<vector<Node*>> NodesWithLevels(parent.size());
        for(int i = 1;i<parent.size();i++){
            Nodes[parent[i]]->children.push_back(Nodes[i]);
            Nodes[i]->op = op[i];
            Nodes[i]->score = score[i];
            Nodes[i]->parent = Nodes[parent[i]];
        }

        dfs(Nodes[0],0);
        for(auto t:Nodes){
            NodesWithLevels[t->level].push_back(t);
        }

        for(int i = NodesWithLevels.size()-1;i >= 0 ;i--){
            for(int o = 0;o<NodesWithLevels[i].size();o++){
                Node* curr = NodesWithLevels[i][o];
                // if(hasSelfOrParentReset(curr)) continue;
                if(curr->op == 0){
                    //Optional, check if it has a negative subtree
                    long long resetBranchValue;
                    //Need smallest value first
                    int smallestIndex = -1;
                    int smallestValue = INT32_MAX;
                    for(int u = 0;u<curr->children.size();u++){
                        Node* child = curr->children[u];
                        int val = 0;
                        if(!(child->hasReset)) val = child->subtreeValue;
                        if(smallestValue > val){
                            smallestIndex = u;
                            smallestValue = val;
                        }
                    }
                    if(smallestIndex == -1) continue; //It's a leaf
                    //Since it's optional, We'll only do it if it has a negative value
                    if(smallestValue < 0){
                        curr->children[smallestIndex]->hasReset = true;
                        resetBranchValue = curr->children[smallestIndex]->subtreeValue;
                        Node* p = curr;
                        while(p){
                            p->subtreeValue -= resetBranchValue;
                            p = p->parent;
                        }
                    }
                }else if(curr->op == 1){
                    //Optional, check if it has a negative subtree
                    long long resetBranchValue;
                    //Need smallest value first
                    int smallestIndex = -1;
                    int smallestValue = INT32_MAX;
                    for(int u = 0;u<curr->children.size();u++){
                        Node* child = curr->children[u];
                        int val = 0;
                        if(!(child->hasReset)) val = child->subtreeValue;
                        if(smallestValue > val){
                            smallestIndex = u;
                            smallestValue = val;
                        }
                    }
                    if(smallestIndex == -1) continue; //It's a leaf

                    curr->children[smallestIndex]->hasReset = true;
                    resetBranchValue = curr->children[smallestIndex]->subtreeValue;
                    Node* p = curr;
                    while(p){
                        p->subtreeValue -= resetBranchValue;
                        p = p->parent;
                    }
                }
            
            }
        }

        // stack<Node*> s;
        // map<Node*,bool> visited;
        // s.push(Nodes[0]);
        // while (!s.empty()) {
        //     Node* curr = s.top();
        //     s.pop();
        //     if(hasSelfOrParentReset(curr)) continue;
        //     for(auto t:curr->children){
        //         if(!visited[t]){
        //             s.push(t);
        //             visited[t] = true;
        //         }
        //     }
        //     if(curr->op == 0){
        //         //Optional, check if it has a negative subtree
        //         long long resetBranchValue;
        //         //Need smallest value first
        //         int smallestIndex = -1;
        //         int smallestValue = INT32_MAX;
        //         for(int u = 0;u<curr->children.size();u++){
        //             Node* child = curr->children[u];
        //             int val = 0;
        //             if(!(child->hasReset)) val = child->subtreeValue;
        //             if(smallestValue > val){
        //                 smallestIndex = u;
        //                 smallestValue = val;
        //             }
        //         }
        //         if(smallestIndex == -1) continue; //It's a leaf
        //         //Since it's optional, We'll only do it if it has a negative value
        //         if(smallestValue < 0){
        //             curr->children[smallestIndex]->hasReset = true;
        //             resetBranchValue = curr->children[smallestIndex]->subtreeValue;
        //             Node* p = curr;
        //             while(p){
        //                 p->subtreeValue -= resetBranchValue;
        //                 p = p->parent;
        //             }
        //         }
        //     }else if(curr->op == 1){
        //         //Optional, check if it has a negative subtree
        //         long long resetBranchValue;
        //         //Need smallest value first
        //         int smallestIndex = -1;
        //         int smallestValue = INT32_MAX;
        //         for(int u = 0;u<curr->children.size();u++){
        //             Node* child = curr->children[u];
        //             int val = 0;
        //             if(!(child->hasReset)) val = child->subtreeValue;
        //             if(smallestValue > val){
        //                 smallestIndex = u;
        //                 smallestValue = val;
        //             }
        //         }
        //         if(smallestIndex == -1) continue; //It's a leaf

        //         curr->children[smallestIndex]->hasReset = true;
        //         resetBranchValue = curr->children[smallestIndex]->subtreeValue;
        //         Node* p = curr;
        //         while(p){
        //             p->subtreeValue -= resetBranchValue;
        //             p = p->parent;
        //         }
        //     }
        // }
        // for(int i = Nodes.size()-1;i >=0;i--){
        //     Node* curr = Nodes[i];
        //     if(hasSelfOrParentReset(curr)) continue;
        //     if(curr->op == 0){
        //         //Optional, check if it has a negative subtree
        //         long long resetBranchValue;
        //         //Need smallest value first
        //         int smallestIndex = -1;
        //         int smallestValue = INT32_MAX;
        //         for(int u = 0;u<curr->children.size();u++){
        //             Node* child = curr->children[u];
        //             int val = 0;
        //             if(!(child->hasReset)) val = child->subtreeValue;
        //             if(smallestValue > val){
        //                 smallestIndex = u;
        //                 smallestValue = val;
        //             }
        //         }
        //         if(smallestIndex == -1) continue; //It's a leaf
        //         //Since it's optional, We'll only do it if it has a negative value
        //         if(smallestValue < 0){
        //             curr->children[smallestIndex]->hasReset = true;
        //             resetBranchValue = curr->children[smallestIndex]->subtreeValue;
        //             Node* p = curr;
        //             while(p){
        //                 p->subtreeValue -= resetBranchValue;
        //                 p = p->parent;
        //             }
        //         }
        //     }else if(curr->op == 1){
        //         //Optional, check if it has a negative subtree
        //         long long resetBranchValue;
        //         //Need smallest value first
        //         int smallestIndex = -1;
        //         int smallestValue = INT32_MAX;
        //         for(int u = 0;u<curr->children.size();u++){
        //             Node* child = curr->children[u];
        //             int val = 0;
        //             if(!(child->hasReset)) val = child->subtreeValue;
        //             if(smallestValue > val){
        //                 smallestIndex = u;
        //                 smallestValue = val;
        //             }
        //         }
        //         if(smallestIndex == -1) continue; //It's a leaf

        //         curr->children[smallestIndex]->hasReset = true;
        //         resetBranchValue = curr->children[smallestIndex]->subtreeValue;
        //         Node* p = curr;
        //         while(p){
        //             p->subtreeValue -= resetBranchValue;
        //             p = p->parent;
        //         }
        //     }
        // }

        return Nodes[0]->subtreeValue;    
    }
};

int main(){
// vector<int> height = {1,2,3,1000,9};
// vector<int> parent = {-1, 0, 0, 0, 1, 2, 3, 3};
// vector<int> op = {1, 1, 0, 0, 1, 1, 0, 1};
// vector<int> score = {5, 6, 1, 2, 3, 2, 3, -3};
// vector<int> parent = {-1, 0, 0};
// vector<int> op = {0, 0, 0};
// vector<int> score = {1, 2, 3};
// vector<int> parent = {-1};
// vector<int> op = {1};
// vector<int> score = {-10};
vector<int> parent = {-1,7,9,4,6,3,2,8,5,0};
vector<int> op = {0,0,0,0,0,0,0,1,1,1};
vector<int> score = {-5781,-5054,-9137,-5366,646,-949,-9877,-8389,8162,-3600};
    auto answer = Solution().maxScore(parent,op,score);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
