#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n < 0) return false;
        
        int count = __builtin_popcount(n);
        
        return (count==1);
    }
};

int main(){
    auto answer = Solution().isPowerOfTwo(-2147483648);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
