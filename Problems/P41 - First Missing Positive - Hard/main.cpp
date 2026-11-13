#include <iostream>
#include <bits/stdc++.h>
#include <system_error>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for(int i = 0;i<nums.size();i++){
            int val = nums[i];
            if(val > nums.size() || val <= 0){
                nums[i] = 0;
            }else{
                int temp = nums[val-1];
                if(temp > nums.size() || temp <= 0){
                    temp=0;
                    nums[val-1] = val;
                    nums[i] = temp;
                }else{
                    if(temp == nums[i]){
                        continue;
                    }
                    nums[val-1] = val;
                    nums[i] = temp;
                    if(nums[i] != i+1) i--;
                }

            }
        }
        int biggest =1;
        for(int i =0 ;i<nums.size();i++){
            if(nums[i] == 0 || nums[i]!=i+1){
                return i+1;
            }else{
                biggest++;
            }
        }
        return biggest;
    }
};

int main(){
    vector<int> nums = {1, 2, 0};
    vector<int> nums2 = {3, 4, -1, 1};
    vector<int> nums3 = {2,2};
    auto answer = Solution().firstMissingPositive(nums);
    auto answer2 = Solution().firstMissingPositive(nums2);
    auto answer3 = Solution().firstMissingPositive(nums3);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    std::cout << answer2 <<endl;
    std::cout << answer3 <<endl;
    return 0;
}
