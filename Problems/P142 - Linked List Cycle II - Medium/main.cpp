#include <cstddef>
#include <iostream>
#include <bits/stdc++.h>
#include <type_traits>
#include <unordered_map>

using namespace std;



struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_map<ListNode*, bool> visited;
        while (head!=nullptr) {
            if(visited.count(head) == 0){
                visited[head] = true;
                head = head->next;
            }else{
                return head;
            }
        }
        return NULL;
    }
};

int main(){
    ListNode* first = new ListNode(3);
    ListNode* second = new ListNode(2);
    ListNode* third = new ListNode(0);
    ListNode* fourth = new ListNode(-4);
    first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = second;
    auto answer = Solution().detectCycle(first);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
