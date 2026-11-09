#include <cmath>
#include <cstdint>
#include <iostream>
#include <bits/stdc++.h>
#include <type_traits>
#include <vector>

using namespace std;
class TreeAncestor {
    vector<vector<int>> up;
    int LOG_MAX = log2(INT32_MAX); // This way I'll have LOG_MAX elements to the parent which is the most we'll need
    public:
    TreeAncestor(int n, vector<int>& parent) {
        //Create the entire vector early in case a node has a parent that's not yet mentioned,
        //And the 0 will get overwritten by the -1 from the parent of root
        up = vector<vector<int>>(n,vector<int>(LOG_MAX,0));  

            // cout << "Parent of " << i << " is " << parent[i]<<endl;
        for(int j = 1;j<LOG_MAX;j++){
            // We're gonna get the first parent of every node first,
            //This fixed an issue because parent[i] > i
            for(int i =0;i<n;i++){ 
            // cout << "Getting Anccestory of " << i <<endl;
            up[i][0] = parent[i];
            if(up[i][j-1] == -1) {
                up[i][j] = -1;
                continue;
            }else{
                up[i][j] = up[up[i][j-1]][j-1];
            }
            // cout << "2^i Parent of " << i << " is " << up[i][j]<<endl;
        }
        }


    }
    
    int getKthAncestor(int node, int k) {
        int parent = node;
        for(int i = 0;i<LOG_MAX;i++){
            //This works because basically every number can be represented as a power of 2
            //It takes some time to wrap your head around it but basically for 5
            //5 = 0b101
            //first pass it does a jump for i = 0, So the direct parent (Now we're at the direct parent)
            //then i = 1 doesn't do anything
            //then i = 2 it works and goes to the 2nd Parent
            //
            // node5 <- When i = 2 we jump here, (parent = node5)
            // node4 
            // node3
            // node2 <- When i = 0 we jump here, (parent = node2)
            // node1 <- We started here (Set parent = node1)
            if(k & (1 << i)){
                parent = up[parent][i];
                if(parent == -1) return -1;
            }
        }
        return parent;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */

int main(){
    vector<int> parents = {-1,2,3,0};
    auto answer = TreeAncestor(4,parents);
    
    std::cout << answer.getKthAncestor(2,3) <<endl;
    std::cout << answer.getKthAncestor(2,2) <<endl; // This used to fail (should be 0)
    std::cout << answer.getKthAncestor(2,1) <<endl;

    parents = {-1,0,0,0,3};
    answer = TreeAncestor(5,parents);
    
    std::cout << answer.getKthAncestor(1,5) <<endl;
    std::cout << answer.getKthAncestor(3,2) <<endl; // This used to fail (should be 0)
    std::cout << answer.getKthAncestor(0,1) <<endl;
    std::cout << answer.getKthAncestor(3,1) <<endl;
    std::cout << answer.getKthAncestor(3,5) <<endl;

    parents = {-1,0,0,5,1,1,5};
    answer = TreeAncestor(7,parents);
    
    std::cout << answer.getKthAncestor(3,2) <<endl;
    std::cout << answer.getKthAncestor(5,2) <<endl; // This used to fail (should be 0)
    std::cout << answer.getKthAncestor(6,3) <<endl;
    
    return 0;
}