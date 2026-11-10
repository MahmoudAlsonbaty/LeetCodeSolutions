#include <cstddef>
#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

 class Solution {
    public:
    void reorderList(ListNode* head) {
        unordered_map<int, ListNode*> list;
        int counter = 1;
        while(head != nullptr){
            list[counter] = head;
            counter++;
            head = head->next;
        }
        int n = counter-1; // counter will increment once after the last element
        int reverseCounter = n; // counter will increment once after the last element
        head = list[1];
        for(int i = 1;i<=n/2 ;i++){
            head->next=list[reverseCounter];
            head=head->next;
            head->next=list[i+1];
            head=head->next;
            reverseCounter--;
        }
        head->next = nullptr;
        head = list[1];
    }
};

int main(){
    ListNode* head = new ListNode(1,new ListNode(2, new ListNode(3,new ListNode(4,new ListNode(5)))));
    // auto answer = Solution().reorderList(head);
    Solution().reorderList(head);
    while(head != nullptr){
        cout << head->val <<endl;
        head = head->next;
    }
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // std::cout << answer <<endl;
    return 0;
}
