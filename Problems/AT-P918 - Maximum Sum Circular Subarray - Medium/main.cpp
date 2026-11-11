#include <cstdint>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int nextE(int i,vector<int>& nums){
        if(i == nums.size()-1){
            return 0;
        }else{
            return i+1;
        }
    }

    int maxSubarraySumCircular(vector<int>& nums) {
        long long maxi = INT32_MIN;
        for(int i =0;i<nums.size();i++){
            long long sum = nums[i];
            maxi = max(maxi,sum);
            for(int j =nextE(i,nums);j!=i;j=nextE(j,nums)){
                if(j==nums.size()) break;
                sum+=nums[j];
                maxi = max(maxi,sum);
            }   
        }    
        return maxi;
    }
};

int main(){
vector<int> nums = {-3, -2, -3};
    auto answer = Solution().maxSubarraySumCircular(nums);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
