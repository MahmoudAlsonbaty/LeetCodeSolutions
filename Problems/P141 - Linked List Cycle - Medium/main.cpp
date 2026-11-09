#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

//   Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
    bool hasCycle(ListNode *head) {
        bool hasCycle = false;
        unordered_map<ListNode*,bool> visited;
        while(head != NULL){
            if(visited.count(head) != 0){
                hasCycle = true;
                break;
            }else{
                visited[head] = true;
                head = head->next;
            }
        }     
        
        return hasCycle;
    }
};

int main(){

        // auto answer = Solution().hasCycle();
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // std::cout << answer <<endl;
    return 0;
}