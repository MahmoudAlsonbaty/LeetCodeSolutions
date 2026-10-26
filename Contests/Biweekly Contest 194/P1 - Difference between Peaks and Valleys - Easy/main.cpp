#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int peakValleyDifference(vector<int>& nums) {
        int sumOfPeaks = 0;
        int sumOfValleys = 0;

        for(int i = 1;i<nums.size()-1;i++){
            if(nums[i] > nums[i-1] && nums[i] > nums[i+1]){
                sumOfPeaks += nums[i];
                continue;
            }
            if(nums[i] < nums[i-1] && nums[i] < nums[i+1]){
                sumOfValleys += nums[i];
            }
        }
        return (sumOfPeaks-sumOfValleys);
    }
};

int main(){
    vector<int> example = {-5,-6,-1,-2,5,3,2};
    auto answer = Solution().peakValleyDifference(example);

    std::cout << answer <<endl;
    return 0;
}
