#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class MyQueue {
    stack<int> mainStack;
    stack<int> helpStack;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        while (!mainStack.empty()) {
            helpStack.push(mainStack.top());
            mainStack.pop();
        }
        mainStack.push(x);
        while (!helpStack.empty()) {
            mainStack.push(helpStack.top());
            helpStack.pop();
        }
    }
    
    int pop() {
        int t = mainStack.top();
        mainStack.pop();
        return t;
    }
    
    int peek() {
        return mainStack.top();
    }
    
    bool empty() {
        return mainStack.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main(){
    MyQueue* obj = new MyQueue();
    obj->push(5);
    obj->push(4);
    obj->push(2);
    int param_2 = obj->pop();
    int param_5 = obj->pop();
    int param_3 = obj->peek();
    bool param_4 = obj->empty();
    // auto answer = Solution().MyQueue();
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // std::cout << answer <<endl;
    return 0;
}
