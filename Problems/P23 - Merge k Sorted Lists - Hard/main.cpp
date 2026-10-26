#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <vector>

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<int,vector<int>,greater<int>> myQ;
        for(int i = 0;i<lists.size();i++){
            while(true){
                if(lists[i] == nullptr) break;
                myQ.push(lists[i]->val);
                if(lists[i]->next == nullptr) break;
                lists[i] = lists[i]->next;
            }
        }
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        while(!myQ.empty()){
            ListNode* current = new ListNode(myQ.top());
            myQ.pop();

            if(head == nullptr){
                head = current;
                tail = current;
            }else{
                tail->next = current;
                tail = tail->next;
            }

        }
        return head;
    }
};

int main(){
    ListNode* list1 = new ListNode(1,new ListNode(4,new ListNode(5)));
    ListNode* list2 = new ListNode(1,new ListNode(3,new ListNode(4)));
    ListNode* list3 = new ListNode(2,new ListNode(6));
    ListNode* list4 = new ListNode();
    vector<ListNode*> testCase = {list1,list2,list3};
    vector<ListNode*> testCase2 = {nullptr};

    auto answer = Solution().mergeKLists(testCase);
    
    std::cout << answer <<endl;
    return 0;
}
