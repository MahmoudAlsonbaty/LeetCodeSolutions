#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int longestSeq = 0;
        //Sliding Window Problem
        int left = 0;
        unordered_map<char,int> freq;
        for(int right =0;right<s.length();right++){            
                if(freq.count(s[right]) != 0){
                    while(left <= freq[s[right]]){
                        freq.erase(s[left]);
                        left++;
                    }
                    freq[s[right]] = right;
                }else{
                    freq[s[right]] = right;
                    longestSeq = max(longestSeq,right - left+1);
                }
        }
        return longestSeq;
    }
};


int main(){
    auto answer = Solution().lengthOfLongestSubstring("pwwkew");
    std::cout << answer <<endl;
    return 0;
}
