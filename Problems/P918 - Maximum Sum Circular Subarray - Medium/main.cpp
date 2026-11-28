#include <cstdint>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:


    int maxSubarraySumCircular(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        long long CurrSum = 0;
        long long maxSum = nums[0];
        int maxElements = nums.size();

        vector<int> flip = nums;
        nums.insert(nums.end(),flip.begin(),flip.end());

        int currentElements = 0;
        for(int i = 0;i<nums.size();i++){
            if(currentElements == maxElements){
                CurrSum = max(CurrSum,0LL);
                if(CurrSum == 0){
                    currentElements =1;
                    CurrSum+=nums[i];
                    maxSum = max(maxSum,CurrSum);
                    continue;
                }
                CurrSum-=nums[i-maxElements];
                currentElements--;
                maxSum = max(maxSum,CurrSum);
                int windowStart = i - currentElements;
                long long prefix = 0, minPrefix = 0;
                int dropCount = 0;
                for(int j = windowStart; j < i; j++){
                    prefix += nums[j];
                    if(prefix < minPrefix){
                        minPrefix = prefix;
                        dropCount = j - windowStart + 1;
                    }
                }
                CurrSum -= minPrefix;
                currentElements -= dropCount;
                CurrSum+=nums[i];
                currentElements++;
                maxSum = max(maxSum,CurrSum);
            }else{
                CurrSum = max(CurrSum,0LL);
                if(CurrSum == 0){
                    currentElements =1;
                }else{
                    currentElements++;
                }
                CurrSum+=nums[i];
                maxSum = max(maxSum,CurrSum);
            }
       }
       return maxSum;
    }
};

int main(){
// vector<int> nums = {-3, -2, -3};
// vector<int> nums = {1,-2,3,-2};
// vector<int> nums = {5,-3,5};
vector<int> nums = {-5,-2,5,6,-2,-7,0,2,8};
    auto answer = Solution().maxSubarraySumCircular(nums);
    // auto answer = kadanes(nums);

    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
