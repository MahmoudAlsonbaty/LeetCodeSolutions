#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class MyCircularQueue {
    int getNext(int a){
        if(a+1 == FullSize){
            return 0;
        }else{
            return a+1;
        }
    }
public:
    int* arr;
    int front = 0;
    int back = 0;
    int size = 0;
    int FullSize;

    MyCircularQueue(int k) {
        arr = new int[k];
        FullSize = k;
    }
    
    bool enQueue(int value) {
        if(isEmpty()){
            arr[0] = value;
            front = 0;
            back = 0;
            size++;
            return true;
        }else{
            if(getNext(back) == front){
                return false;
            }else {
                back = getNext(back);
                arr[back] = value;
                size++;
                return true;
            }
        }
    }
    
    bool deQueue() {
        if(isEmpty()){
            return false;
        }else{
            arr[front] = 0;
            front = getNext(front);
            size--;
            return true;
        }
    }
    
    int Front() {
        if(!isEmpty()){
            return arr[front];
        }else{
            return -1;
        }
    }
    
    int Rear() {
        if(!isEmpty()){
            return arr[back];
        }else{
            return -1;
        }
    }
    
    bool isEmpty() {
        return size==0;
    }
    
    bool isFull() {
        return size == FullSize;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

int main(){

    auto answer = MyCircularQueue(3);
    answer.enQueue(1);
    answer.enQueue(2);
    answer.enQueue(3);
    answer.enQueue(4);
    int a = answer.Rear();
    int b = answer.Front();
    auto c = answer.isFull();
    answer.deQueue();

    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // std::cout << answer <<endl;
    return 0;
}
