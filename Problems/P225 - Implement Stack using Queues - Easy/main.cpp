#include <iostream>
#include <bits/stdc++.h>
#include <queue>

using namespace std;

class MyStack {
public:
    queue<int> main;
    queue<int> assist;
    MyStack() {
        
    }
    
    void push(int x) {
        while (!main.empty()) {
            int t = main.front();
            main.pop();
            assist.push(t);
        }
        main.push(x);
        while (!assist.empty()) {
            int t = assist.front();
            assist.pop();
            main.push(t);
        }
    }
    
    int pop() {
        int t = main.front();
        main.pop();
        return t;
    }
    
    int top() {
        return main.front();
    }
    
    bool empty() {
        return main.empty();
    }
};




int main(){
    MyStack* obj = new MyStack();
    obj->push(4);
    int param_2 = obj->pop();
    int param_3 = obj->top();
    bool param_4 = obj->empty();

    // auto answer = Solution().MyStack();
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // std::cout << answer <<endl;
    return 0;
}
