#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <queue>
#include <unordered_map>
using namespace std;

class ProductOfNumbers {
public:
    stack<int> mainQ;
    ProductOfNumbers() {
    }
    
    void add(int num) {
        mainQ.push(num);
    }
    
    int getProduct(int k) {
        stack<int> auxQ;
        int sum = 1;
        for(int i = 0;i<k;i++){
            sum *= mainQ.top();
            auxQ.push(mainQ.top());
            mainQ.pop();
        }  
        while(!auxQ.empty()){
            mainQ.push(auxQ.top());
            auxQ.pop();
        }
        return sum;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */



int main(){

    ProductOfNumbers prods;
    prods.add(1);
    prods.add(2);
    prods.add(3);
    prods.add(4);
    prods.add(5);
    prods.add(6);

    cout << prods.getProduct(2);
    cout << prods.getProduct(2);
    cout << prods.getProduct(2);
    cout << prods.getProduct(2);
    cout << prods.getProduct(2);
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
