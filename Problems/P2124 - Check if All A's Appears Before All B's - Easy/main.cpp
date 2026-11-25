#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    bool checkString(string s) {
        //A's before B's
        for(int i =0;i<s.length()-1;i++){
            if(s[i] == 'b'){
                if(s[i+1] =='a'){
                    return false;
                }
            }
        }
        return true;
    }
};



int main(){
    string s = "aaabbb";
    auto answer = Solution().checkString(s);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
