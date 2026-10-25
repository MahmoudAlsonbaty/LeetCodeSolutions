#include <iostream>
#include <bits/stdc++.h>

using namespace std;
    // Definition for singly-linked list.
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> sum;
        bool L1Next = true;
        bool L2Next = true;
        int carry = 0;
        for(int i = 0;i<100;i++){
            int total = carry;
            carry = 0;
            if(L1Next){
                total += l1->val;
                if(l1->next != nullptr){
                    l1 = l1->next;
                }else{
                    L1Next = false;
                }
            }
            if(L2Next){
                total += l2->val;
                if(l2->next != nullptr){
                    l2 = l2->next;
                }else{
                    L2Next = false;
                }
            }
            carry = total /10;
            total = total %10;
            sum.push_back(total);
            if(L1Next == false && L2Next == false && carry == 0){
                break;
            }
        }

        ListNode* sumNode = new ListNode();
        ListNode* ref = sumNode;
        for(int i = 0;i<sum.size();i++){
            ref->val = sum[i];
            if(i+1 != sum.size()){
                ref->next = new ListNode();
                ref = ref->next;
            } 
        }
        return sumNode;

    }
};


int main(){
    ListNode* A1 = new ListNode(2,new ListNode(4,new ListNode(3)));
    ListNode* A2 = new ListNode(5,new ListNode(6,new ListNode(4)));
    auto answer = Solution().addTwoNumbers(A1,A2);
    while(answer->next != nullptr){
        cout << answer->val << " ";
        answer = answer->next;
    }
        cout << answer->val << " ";

    return 0;
}
