#include <cstddef>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* const sol = head;
        vector<ListNode*> his = {head};
        head = head->next;
        while (head != nullptr) {
            his.push_back(head);
            head = head->next;
        }
        if(n == his.size()){
            return sol->next;
        }
        if(n == 1){
            if(his.size() ==1){
                return nullptr;
            }
            his[his.size()-n-1]->next=nullptr;
        }else{
            his[his.size()-n-1 ]->next=his[his.size()-n+1];
        }
        return sol;
    }
};

int main(){
    ListNode* head = new ListNode(1,new ListNode(2,new ListNode(3,new ListNode(4,new ListNode(5)))));
    auto answer = Solution().removeNthFromEnd(head,2);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    while (head!=nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    // std::cout << answer <<endl;
    return 0;
}
