#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    bool canAliceWin(int n) {
        if(n < 10) return false;
        int start = 10;
        while(n>0){
            if(n < start) return false; // Alice Fails
            n -= start; // Alice Made it, Get it ready for Bob
            start--;// Make start 1 less
            if(n < start) return true; // Bob can't take stone, Alice Wins
            n -= start;
            start--;// Next turn would be Alice
        }
        if(n < start) return false;
        return true;
    }
};



int main(){

    // auto answer = Solution().canAliceWin();
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
