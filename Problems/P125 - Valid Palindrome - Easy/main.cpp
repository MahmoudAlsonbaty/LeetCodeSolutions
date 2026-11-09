#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;
class Solution {
public:
    bool isPalindrome(string s) {
        bool sol = true;
        for(int i = 0;i < s.size();i++){
            if((s[i] >= 65 && s[i] <= 90) ||  (s[i] >= 97 && s[i] <= 122) ||  (s[i] >= 48 && s[i] <= 57)){
                continue;
            }else{
                s.erase(s.begin()+i);
                i--;
            }
        }
        int e = s.size()-1;
        for(int i = 0;i < s.size()/2;i++){
            if(tolower(s[i]) != tolower(s[e])){
                return false;
            }
            e--;
        }
        return sol;
    }
};

int main(){
    auto answer = Solution().isPalindrome("0P");
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
