#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string longest = "";
        int shortest = INT32_MAX;
        for(auto it: strs){
            if(it.length() < shortest){
                shortest = it.length();
            }
        }
        for(int i = 0;i<shortest;i++){
            bool same = true;
            char last = strs[0][i];
            for(int j = 0;j<strs.size();j++){
                if(strs[j][i] == last){
                    continue;
                }else{
                    same = false;
                    break;
                }
            }
            if(same){
                longest += last;
            }else{
                break;
            }
        }
        return longest;
    }
};
int main(){
    vector<string> example = {"dog","racecar","car"};
    auto answer = Solution().longestCommonPrefix(example);
    std::cout << answer ;
    return 0;
}
