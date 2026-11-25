#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        // 0 first, 1 second, 2 third; 
        int of0 =0;
        for(int i = 0;i<nums.size();i++){
            if(nums[i] == 0){
                swap(nums[of0],nums[i]);
                of0++;
            }
        }
        for(int i = of0;i<nums.size();i++){
            if(nums[i] == 1){
                swap(nums[of0],nums[i]);
                of0++;
            }
        }
        for(int i = of0;i<nums.size();i++){
            if(nums[i] == 2){
                swap(nums[of0],nums[i]);
                of0++;
            }
        }
    }
};



int main(){
    vector<int> nums = {2, 0, 2, 1, 1, 0};
    Solution().sortColors(nums);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    coutVector(&nums);     // vector<T>
    // coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
