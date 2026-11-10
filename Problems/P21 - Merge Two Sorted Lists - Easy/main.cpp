#include <cstdint>
#include <iostream>
#include <bits/stdc++.h>

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* sol = new ListNode(INT32_MIN);
        ListNode* head = sol;
        int list1Val = INT32_MAX;
        int list2Val = INT32_MAX;
        bool headSet = false;
        while(list1 != nullptr || list2 != nullptr){
            
            list1Val = (list1 == nullptr) ? INT32_MAX : list1->val;
            list2Val = (list2 == nullptr) ? INT32_MAX : list2->val;
           
            if(list1Val < list2Val){
                if(sol != nullptr && sol->val == INT32_MIN){
                    sol->val = list1->val;
                    list1 = list1->next;
                    continue;
                }
                sol->next = new ListNode(list1->val);
                // sol->val = list1->val;
                list1 = list1->next;
                // sol->next = new ListNode();
                sol = sol->next;
            }else if(list1Val > list2Val){
                if(sol != nullptr && sol->val == INT32_MIN){
                    sol->val = list2->val;
                    list2 = list2->next;
                    continue;
                }
                sol->next = new ListNode(list2->val);
                // sol->val = list2->val;
                list2 = list2->next;
                // sol->next = new ListNode();
                sol = sol->next;
            }else{
                if(sol != nullptr && sol->val == INT32_MIN){
                    sol->val = list2->val;
                    list2 = list2->next;
                    sol->next = new ListNode(list1->val);
                    sol = sol->next;
                    list1 = list1->next;
                    continue;
                }
                sol->next = new ListNode(list1->val);
                // sol->val = list1->val
                // sol->next = new ListNode();
                sol = sol->next;
                sol->next = new ListNode(list2->val);
                // sol->val = list2->val;
                // sol->next = new ListNode();
                sol = sol->next;
                list1 = list1->next;
                list2 = list2->next;
            }
        }
        if(head->val == INT32_MIN) return nullptr;
        return head;
    }
};


int main(){
    ListNode* head = new ListNode(1,new ListNode(2, new ListNode(3,new ListNode(4,new ListNode(5)))));
    ListNode* head2 = new ListNode(1,new ListNode(3, new ListNode(7,new ListNode(8,new ListNode(9)))));
    // auto answer = Solution().reorderList(head);
    ListNode* sol = Solution().mergeTwoLists(head,head2);
    while(sol != nullptr){
        cout << sol->val <<endl;
        sol = sol->next;
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
