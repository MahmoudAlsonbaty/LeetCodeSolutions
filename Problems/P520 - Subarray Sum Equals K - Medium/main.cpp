#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        // Generate Prefix Sum
        vector<int> prefixSum(nums.size()+1,0);
        long int sum = 0;
        for(int i = 1; i<=nums.size();i++){
            sum+=nums[i-1];
            prefixSum[i] = sum;
            for(int j = 0;j<i;j++){
                int currSum = prefixSum[i] - prefixSum[j];
                if(currSum == k) count++;
            }
        }
        return count;
    }
};

int main(){

    return 0;
}