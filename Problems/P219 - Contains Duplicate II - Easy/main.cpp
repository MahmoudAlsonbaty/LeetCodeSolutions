#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,vector<int>> freqAndLoc;
        for(int i =0;i<nums.size();i++){
            if(freqAndLoc.count(nums[i]) != 0){
                //We gota duplicate, Check the condition
                for(auto t:freqAndLoc[nums[i]]){
                    if(i - t <= k) return true;
                }
                // Condition not met so let's insert ourselves
                freqAndLoc[nums[i]].push_back(i);
            }else{
                freqAndLoc[nums[i]] = {i};
            }
        }
        return false;
    }
};



int main(){
// vector<int> nums = {1, 2, 3, 1};
// int k = 3;
vector<int> nums = {1, 2, 3, 1, 2, 3};
int k = 2;
    auto answer = Solution().containsNearbyDuplicate(nums,k);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
