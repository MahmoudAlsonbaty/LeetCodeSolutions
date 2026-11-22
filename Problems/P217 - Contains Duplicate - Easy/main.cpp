#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> freq;
        for(auto t:nums){
            if(freq.count(t) != 0) return true;
            freq[t]++;
        }
        return false;
    }
};



int main(){
    vector<int> nums = {1, 2, 3, 5};
    auto answer = Solution().containsDuplicate(nums);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
