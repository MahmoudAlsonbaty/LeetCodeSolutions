#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";
        string res = countAndSay(n-1);
        bool appended = false;
        string newRes="";
        for(int i = 0;i<res.length();i++){
            char c = res[i];
            int add = 1;
            for(int j = i+1;j<=res.length();j++){
                if(j<res.length() && res[j]==c){
                    i = j;
                    add++;
                    continue;
                }else{
                    newRes += to_string(add) + c;
                    break;
                }
            }
        }
        return newRes;
    }
};

int main(){
    auto answer = Solution().countAndSay(4);

    std::cout << answer <<endl;
    return 0;
}
